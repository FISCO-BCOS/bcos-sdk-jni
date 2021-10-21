#include "jni/org_fisco_bcos_sdk_jni_rpc_Rpc.h"
#include "bcos_sdk_c.h"
#include "bcos_sdk_c_common.h"
#include "bcos_sdk_c_rpc.h"
#include "jni/org_fisco_bcos_sdk_common.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <cstddef>
#include <cstdio>
#include <memory>
#include <string>

static std::string obtain_group_params(JNIEnv* env, jobject self)
{
    jclass cls = env->GetObjectClass(self);
    if (!cls)
    {
        env->FatalError("GetObjectClass failed");
    }

    jfieldID groupFieldID = env->GetFieldID(cls, "group", "Ljava/lang/String;");
    if (!groupFieldID)
    {
        env->FatalError("Cannot  GetFieldID, obtain_group_params failed");
    }

    jstring groupString = (jstring)env->GetObjectField(self, groupFieldID);

    const char* group = env->GetStringUTFChars(groupString, NULL);
    if (group == NULL)
    {
        env->FatalError("Cannot  GetStringField, obtain_group_params failed");
    }

    std::string ret(group);
    env->ReleaseStringUTFChars(groupString, group);
    return ret;
}

// receive rpc response and call the cb
static void on_receive_rpc_response(struct bcos_sdk_c_struct_response* resp)
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
        env->GetMethodID(cbClass, "onResponse", "(Lorg/fisco/bcos/sdk/jni/common/Response;)V");

    if (onRespMethodID == NULL)
    {
        env->FatalError("Cannot found onResponse methodID");
    }

    int error = resp->error;
    char* desc = resp->desc ? resp->desc : (char*)"";
    char* data = resp->data ? (char*)resp->data : (char*)"";

    printf(" ## ==> rpc callback, error : %d, msg: %s, data : %s\n", error, desc, data);

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

    // release callback global reference
    env->DeleteGlobalRef(jcallback);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    newNativeObj
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/JniConfig;)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_newNativeObj(
    JNIEnv* env, jclass, jobject jconfig)
{
    // config
    struct bcos_sdk_c_config* config = init_bcos_sdk_c_config(env, jconfig);
    // create rpc obj
    void* rpc = bcos_sdk_create_rpc(config);
    // destroy config
    bcos_sdk_c_config_destroy(config);
    if (rpc == NULL)
    {
        // TODO: how to handler the error
        env->FatalError("bcos_sdk_create_rpc return NULL");
    }

    return reinterpret_cast<jlong>(rpc);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_start(JNIEnv* env, jobject self)
{
    void* rpc = obtain_native_object(env, self);
    bcos_sdk_start_rpc(rpc);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_stop(JNIEnv* env, jobject self)
{
    void* rpc = obtain_native_object(env, self);
    bcos_sdk_stop_rpc(rpc);
}


/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    genericMethod
 * Signature: (Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL
Java_org_fisco_bcos_sdk_jni_rpc_Rpc_genericMethod__Ljava_lang_String_2Lorg_fisco_bcos_sdk_jni_rpc_RpcCallback_2(
    JNIEnv* env, jobject self, jstring jdata, jobject jcallback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(jcallback);
    context->jvm = jvm;

    // data
    const char* data = env->GetStringUTFChars(jdata, NULL);
    bcos_rpc_send_msg(rpc, data, on_receive_rpc_response, context);
    env->ReleaseStringUTFChars(jdata, data);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    genericMethod
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL
Java_org_fisco_bcos_sdk_jni_rpc_Rpc_genericMethod__Ljava_lang_String_2Ljava_lang_String_2Lorg_fisco_bcos_sdk_jni_rpc_RpcCallback_2(
    JNIEnv* env, jobject self, jstring jgroup, jstring jdata, jobject jcallback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);


    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(jcallback);
    context->jvm = jvm;

    // group
    const char* group = env->GetStringUTFChars(jgroup, NULL);
    // data
    const char* data = env->GetStringUTFChars(jdata, NULL);

    bcos_rpc_send_msg_to_group(rpc, group, data, on_receive_rpc_response, context);

    env->ReleaseStringUTFChars(jgroup, group);
    env->ReleaseStringUTFChars(jdata, data);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    genericMethod
 * Signature:
 * (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL
Java_org_fisco_bcos_sdk_jni_rpc_Rpc_genericMethod__Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2Lorg_fisco_bcos_sdk_jni_rpc_RpcCallback_2(
    JNIEnv* env, jobject self, jstring jgroup, jstring jnode, jstring jdata, jobject jcallback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(jcallback);
    context->jvm = jvm;

    // group
    const char* group = env->GetStringUTFChars(jgroup, NULL);
    // node
    const char* node = env->GetStringUTFChars(jnode, NULL);
    // data
    const char* data = env->GetStringUTFChars(jdata, NULL);

    bcos_rpc_send_msg_to_group_node(rpc, group, node, data, on_receive_rpc_response, context);

    env->ReleaseStringUTFChars(jgroup, group);
    env->ReleaseStringUTFChars(jnode, node);
    env->ReleaseStringUTFChars(jdata, data);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    call
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_call(
    JNIEnv* env, jobject self, jstring jto, jstring jdata, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // to
    const char* to = env->GetStringUTFChars(jto, NULL);
    // data
    const char* data = env->GetStringUTFChars(jdata, NULL);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_call(rpc, group, to, data, on_receive_rpc_response, context);

    env->ReleaseStringUTFChars(jto, to);
    env->ReleaseStringUTFChars(jdata, data);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    sendTransaction
 * Signature: (Ljava/lang/String;ZLorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_sendTransaction(
    JNIEnv* env, jobject self, jstring jdata, jboolean jproof, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* data = env->GetStringUTFChars(jdata, NULL);
    // proof
    int proof = (jproof == JNI_TRUE ? 1 : 0);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_send_transaction(rpc, group, data, proof, on_receive_rpc_response, context);

    env->ReleaseStringUTFChars(jdata, data);
}


/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getTransaction
 * Signature: (Ljava/lang/String;ZLorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getTransaction(
    JNIEnv* env, jobject self, jstring jtx_hash, jboolean jproof, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* tx_hash = env->GetStringUTFChars(jtx_hash, NULL);
    // proof
    int proof = (jproof == JNI_TRUE ? 1 : 0);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_transaction(rpc, group, tx_hash, proof, on_receive_rpc_response, context);

    env->ReleaseStringUTFChars(jtx_hash, tx_hash);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getTransactionReceipt
 * Signature: (Ljava/lang/String;ZLorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getTransactionReceipt(
    JNIEnv* env, jobject self, jstring jtx_hash, jboolean jproof, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* tx_hash = env->GetStringUTFChars(jtx_hash, NULL);
    // proof
    int proof = (jproof == JNI_TRUE ? 1 : 0);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_transaction_receipt(rpc, group, tx_hash, proof, on_receive_rpc_response, context);

    env->ReleaseStringUTFChars(jtx_hash, tx_hash);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getBlockByHash
 * Signature: (Ljava/lang/String;ZZLorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getBlockByHash(JNIEnv* env, jobject self,
    jstring jblock_hash, jboolean jonly_header, jboolean jonly_txhash, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* block_hash = env->GetStringUTFChars(jblock_hash, NULL);
    // only_header
    int only_header = (jonly_header == JNI_TRUE ? 1 : 0);
    // only_txhash
    int only_txhash = (jonly_txhash == JNI_TRUE ? 1 : 0);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_block_by_hash(
        rpc, group, block_hash, only_header, only_txhash, on_receive_rpc_response, context);

    env->ReleaseStringUTFChars(jblock_hash, block_hash);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getBlockByNumber
 * Signature: (JZZLorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getBlockByNumber(JNIEnv* env,
    jobject self, jlong jnumber, jboolean jonly_header, jboolean jonly_txhash, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // block number
    long block_number = reinterpret_cast<long>(jnumber);
    // only_header
    int only_header = (jonly_header == JNI_TRUE ? 1 : 0);
    // only_txhash
    int only_txhash = (jonly_txhash == JNI_TRUE ? 1 : 0);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_block_by_number(
        rpc, group, block_number, only_header, only_txhash, on_receive_rpc_response, context);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getBlockHashByNumber
 * Signature: (JLorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getBlockHashByNumber(
    JNIEnv* env, jobject self, jlong jnumber, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    // block number
    long block_number = reinterpret_cast<long>(jnumber);
    // TODO:
    bcos_rpc_get_block_hash_by_number(rpc, group, block_number, on_receive_rpc_response, context);
}


/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getBlockNumber
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getBlockNumber(
    JNIEnv* env, jobject self, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_block_number(rpc, group, on_receive_rpc_response, context);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getCode
 * Signature: (Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getCode(
    JNIEnv* env, jobject self, jstring jaddress, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* address = env->GetStringUTFChars(jaddress, NULL);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_code(rpc, group, address, on_receive_rpc_response, context);
    env->ReleaseStringUTFChars(jaddress, address);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getSealerList
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getSealerList(
    JNIEnv* env, jobject self, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_sealer_list(rpc, group, on_receive_rpc_response, context);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getObserverList
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getObserverList(
    JNIEnv* env, jobject self, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_observer_list(rpc, group, on_receive_rpc_response, context);
}
/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getPbftView
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getPbftView(
    JNIEnv* env, jobject self, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_pbft_view(rpc, group, on_receive_rpc_response, context);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getPendingTxSize
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getPendingTxSize(
    JNIEnv* env, jobject self, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_pending_tx_size(rpc, group, on_receive_rpc_response, context);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getSyncStatus
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getSyncStatus(
    JNIEnv* env, jobject self, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_sync_status(rpc, group, on_receive_rpc_response, context);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getSystemConfigByKey
 * Signature: (Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getSystemConfigByKey(
    JNIEnv* env, jobject self, jstring jkey, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* key = env->GetStringUTFChars(jkey, NULL);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_system_config_by_key(rpc, group, key, on_receive_rpc_response, context);

    env->ReleaseStringUTFChars(jkey, key);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getTotalTransactionCount
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getTotalTransactionCount(
    JNIEnv* env, jobject self, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_total_transaction_count(rpc, group, on_receive_rpc_response, context);
}


/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getPeers
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getPeers(
    JNIEnv* env, jobject self, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_peers(rpc, on_receive_rpc_response, context);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getNodeInfo
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getNodeInfo(
    JNIEnv* env, jobject self, jobject callback)
{
    // rpc obj handler
    void* rpc = obtain_native_object(env, self);

    // Note: The JNIEnv pointer, passed as the first argument to every native method, can only be
    // used in the thread with which it is associated. It is wrong to cache the JNIEnv interface
    // pointer obtained from one thread, and use that pointer in another thread.
    JavaVM* jvm;
    env->GetJavaVM(&jvm);

    cb_context* context = new cb_context();
    context->jcallback = env->NewGlobalRef(callback);
    context->jvm = jvm;

    bcos_rpc_get_node_info(rpc, on_receive_rpc_response, context);
}
