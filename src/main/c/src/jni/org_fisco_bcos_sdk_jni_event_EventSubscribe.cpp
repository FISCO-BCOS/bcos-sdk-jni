#include "jni/org_fisco_bcos_sdk_jni_event_EventSubscribe.h"
#include "bcos_sdk_c.h"
#include "bcos_sdk_c_event_sub.h"
#include "jni/org_fisco_bcos_sdk_common.h"
#include <string>

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

    std::string className = "org/fisco/bcos/sdk/jni/common/Response";
    std::string onRespSig = "(Lorg/fisco/bcos/sdk/jni/common/Response)V";
    // void onResponse(Response)
    jmethodID onRespMethodID = env->GetMethodID(cbClass, "onResponse", onRespSig.c_str());
    if (onRespMethodID == NULL)
    {
        env->FatalError(("No such method in the class, className: " + className +
                         " ,method: onResponse ,signature: " + onRespSig)
                            .c_str());
    }

    int error = resp->error;
    char* desc = resp->desc ? resp->desc : (char*)"";
#if defined(_BCOS_SDK_JNI_DEBUG_)
    char* data = resp->data ? (char*)resp->data : (char*)"";

    printf(
        " ## ==> event sub response callback, error : %d, msg: %s, data : %s\n", error, desc, data);
#endif

    // Response obj construct begin
    jclass responseClass = env->FindClass(className.c_str());
    if (responseClass == NULL)
    {
        env->FatalError(("No such class, className: " + className).c_str());
    }

    jmethodID mid = env->GetMethodID(responseClass, "<init>", "()V");
    jobject responseObj = env->NewObject(responseClass, mid);

    // errorCode
    jfieldID errorCodeFieldID = env->GetFieldID(responseClass, "errorCode", "I");
    if (errorCodeFieldID == NULL)
    {
        env->FatalError(
            ("No such field in the class, className: " + className + " ,fieldName: errorCode")
                .c_str());
    }

    // errorMessage
    jfieldID errorMsgFieldID = env->GetFieldID(responseClass, "errorMessage", "Ljava/lang/String;");
    if (errorMsgFieldID == NULL)
    {
        env->FatalError(
            ("No such field in the class, className: " + className + " ,filedName: errorMessage")
                .c_str());
    }

    // byte[] data
    jfieldID dataFieldID = env->GetFieldID(responseClass, "data", "[B");
    if (errorMsgFieldID == NULL)
    {
        env->FatalError(
            ("No such field in the class, className: " + className + " ,filedName: data").c_str());
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
    try
    {
        // config
        struct bcos_sdk_c_config* config = create_bcos_sdk_c_config_from_java_obj(env, jconfig);
        // create amop obj
        void* amop = bcos_sdk_create_event_sub(config);
        // destroy config
        bcos_sdk_c_config_destroy(config);

        return reinterpret_cast<jlong>(amop);
    }
    catch (const bcos::BcosJniException& _e)
    {
        BCOS_LOG(INFO) << LOG_BADGE("Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_newNativeObj")
                       << LOG_DESC("create event sub native obj failed")
                       << LOG_KV("e", boost::diagnostic_information(_e));
        THROW_JNI_EXCEPTION(env, boost::diagnostic_information(_e));
    }
    return 0;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_start(
    JNIEnv* env, jobject self)
{
    void* event = get_obj_native_member(env, self);
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
    void* event = get_obj_native_member(env, self);
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
    void* event = get_obj_native_member(env, self);
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
    void* event = get_obj_native_member(env, self);
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
