#include "jni/org_fisco_bcos_sdk_jni_event_EventSubscribe.h"
#include "bcos_sdk_c.h"
#include "bcos_sdk_c_event_sub.h"
#include "jni/org_fisco_bcos_sdk_common.h"

static void on_receive_event_sub_response(struct bcos_sdk_c_struct_response* resp)
{
    cb_context* context = (cb_context*)resp->context;

    jobject jcallback = context->jcallback;
    JavaVM* jvm = context->jvm;
    // Note: delete cb_context
    delete context;

    JNIEnv* env;
    jvm->AttachCurrentThread((void**)&env, NULL);

    jclass cbClass = env->GetObjectClass(jcallback);
    // void onResponse(Response)
    jmethodID onRespMethodID =
        env->GetMethodID(cbClass, "onResponse", "(Lorg/fisco/bcos/sdk/jni/common/Response)V");
    if (onRespMethodID == NULL)
    {
        env->FatalError("Cannot found onResponse methodID");
    }

    int error = resp->error;
    char* desc = resp->desc ? resp->desc : (char*)"";
#if 0
    char* data = resp->data ? (char*)resp->data : (char*)"";

     printf(
     " ## ==> event sub response callback, error : %d, msg: %s, data : %s\n", error, desc, data);
#endif

    // Response obj construct begin
    jclass responseClass = env->FindClass("org/fisco/bcos/sdk/jni/common/Response");
    if (responseClass == NULL)
    {
        env->FatalError("Cannot find org.fisco.bcos.sdk.jni.common.Response class");
    }

    jmethodID mid = env->GetMethodID(responseClass, "<init>", "()V");
    jobject responseObj = env->NewObject(responseClass, mid);

    // errorCode
    jfieldID errorCodeFieldID = env->GetFieldID(responseClass, "errorCode", "I");
    if (errorCodeFieldID == NULL)
    {
        env->FatalError("Cannot find errorCodeFieldID fieldID");
    }

    // errorMessage
    jfieldID errorMsgFieldID = env->GetFieldID(responseClass, "errorMessage", "Ljava/lang/String;");
    if (errorMsgFieldID == NULL)
    {
        env->FatalError("Cannot find errorMsgFieldID fieldID");
    }

    // byte[] data
    jfieldID dataFieldID = env->GetFieldID(responseClass, "data", "[B");
    if (errorMsgFieldID == NULL)
    {
        env->FatalError("Cannot find data fieldID");
    }

    jstring errorString = env->NewStringUTF(desc);
    env->SetLongField(responseObj, errorCodeFieldID, jint(error));
    env->SetObjectField(responseObj, errorMsgFieldID, errorString);

    jbyteArray byteArrayObj = env->NewByteArray(resp->size);
    if (resp->size > 0)
    {
        jbyte* data = (jbyte*)resp->data;
        env->SetByteArrayRegion(byteArrayObj, 0, resp->size, data);
    }
    env->SetObjectField(responseObj, dataFieldID, byteArrayObj);

    env->CallObjectMethod(jcallback, onRespMethodID, responseObj);

    //  Note: the callback should not be unreference, it is not
    // once used
    // env->DeleteGlobalRef(jcallback);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    newNativeObj
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/JniConfig;)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_newNativeObj(
    JNIEnv* env, jclass, jobject jconfig)
{
    // config
    struct bcos_sdk_c_config* config = init_bcos_sdk_c_config(env, jconfig);
    // create amop obj
    void* amop = bcos_sdk_create_event_sub(config);
    // destroy config
    bcos_sdk_c_config_destroy(config);
    if (amop == NULL)
    {
        // TODO: how to handler the error
        env->FatalError("bcos_sdk_create_event_sub return NULL");
    }

    return reinterpret_cast<jlong>(amop);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_start(
    JNIEnv* env, jobject self)
{
    void* event = obtain_native_object(env, self);
    bcos_sdk_start_event_sub(event);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_stop(
    JNIEnv* env, jobject self)
{
    void* event = obtain_native_object(env, self);
    bcos_sdk_stop_event_sub(event);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    subscribeEvent
 * Signature:
 * (Ljava/lang/String;Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/event/EventSubscribeCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_subscribeEvent(
    JNIEnv* env, jobject self, jstring jgroup, jstring jparams, jobject jcallback)
{
    void* event = obtain_native_object(env, self);
    const char* group = env->GetStringUTFChars(jgroup, 0);
    const char* params = env->GetStringUTFChars(jparams, 0);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(jcallback);
    context->jvm = jvm;

    bcos_event_sub_subscribe_event(event, group, params, on_receive_event_sub_response, context);

    // release params
    env->ReleaseStringUTFChars(jparams, params);
    // release group
    env->ReleaseStringUTFChars(jgroup, group);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    unsubscribeEvent
 * Signature: (Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/event/EventSubscribeCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_unsubscribeEvent(
    JNIEnv* env, jobject self, jstring jeventid, jobject jcallback)
{
    void* event = obtain_native_object(env, self);
    const char* eventid = env->GetStringUTFChars(jeventid, 0);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(jcallback);
    context->jvm = jvm;

    bcos_event_sub_unsubscribe_event(event, eventid, on_receive_event_sub_response, context);

    // release params
    env->ReleaseStringUTFChars(jeventid, eventid);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    getAllSubscribedEvents
 * Signature: ()Ljava/util/Set;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_getAllSubscribedEvents(
    JNIEnv*, jobject)
{
    // TODO:
    return jobject();
}
