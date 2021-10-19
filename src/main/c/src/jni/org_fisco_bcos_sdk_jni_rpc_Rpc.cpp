#include "jni/org_fisco_bcos_sdk_jni_rpc_Rpc.h"
#include "bcos_sdk_c.h"
#include "bcos_sdk_c_rpc.h"
#include <bcos-boostssl/websocket/WsTools.h>
#include <stdint.h>
#include <stdio.h>
#include <cstddef>
#include <cstdio>
#include <string>
#include <tuple>
#include <vector>

static void* obtain_rpc_obj(JNIEnv* env, jobject self)
{
    jclass cls = env->GetObjectClass(self);
    if (!cls)
    {
        env->FatalError("Can't GetObjectClass, obtain_rpc_obj failed");
    }

    jfieldID nativeFieldID = env->GetFieldID(cls, "nativeObj", "J");
    if (!nativeFieldID)
    {
        env->FatalError("Can't GetFieldID,  obtain_rpc_obj failed");
    }

    jlong nativeObj = env->GetLongField(self, nativeFieldID);
    void* rpc = reinterpret_cast<void*>(nativeObj);
    if (rpc == NULL)
    {
        env->FatalError("Can't GetFieldID,  obtain_rpc_obj failed");
    }

    printf(" ## ==> rpc native obj: %ld\n", reinterpret_cast<long>(nativeObj));

    return rpc;
}

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
        env->FatalError("Can't GetFieldID, obtain_group_params failed");
    }

    jstring groupString = (jstring)env->GetObjectField(self, groupFieldID);

    const char* group = env->GetStringUTFChars(groupString, NULL);
    if (group == NULL)
    {
        env->FatalError("Can't GetStringField, obtain_group_params failed");
    }

    std::string ret(group);

    printf(" ## ==> group: %s\n", ret.c_str());

    env->ReleaseStringUTFChars(groupString, group);
    return ret;
}

static void handle_rpc_resp_cb(struct bcos_sdk_struct_response* struct_resp)
{
    printf(" ## ==> rpc callback, error : %d, data : %s\n", struct_resp->error,
        (char*)struct_resp->data);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    newNativeObj
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/ConfigOption;)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_newNativeObj(
    JNIEnv* env, jclass, jobject jconfig)
{
    jclass configClass = env->GetObjectClass(jconfig);

    jfieldID threadPoolSizeFieldID = env->GetFieldID(configClass, "threadPoolSize", "I");
    int threadPoolSize = (int)env->GetIntField(jconfig, threadPoolSizeFieldID);

    jfieldID reconnectPeriodMsFieldID = env->GetFieldID(configClass, "reconnectPeriodMs", "I");
    int reconnectPeriodMs = (int)env->GetIntField(jconfig, reconnectPeriodMsFieldID);

    jfieldID heartbeatPeriodMsFieldID = env->GetFieldID(configClass, "heartbeatPeriodMs", "I");
    int heartbeatPeriodMs = (int)env->GetIntField(jconfig, heartbeatPeriodMsFieldID);

    jfieldID messageTimeoutMsFieldID = env->GetFieldID(configClass, "messageTimeoutMs", "I");
    int messageTimeoutMs = (int)env->GetIntField(jconfig, messageTimeoutMsFieldID);

    jfieldID peersFieldID = env->GetFieldID(configClass, "peers", "Ljava/util/List;");
    jobject jpeersOjbect = env->GetObjectField(jconfig, peersFieldID);
    if (jpeersOjbect == NULL)
    {
        env->FatalError("Can't GetObjectField for peers of ConfigOption");
    }

    // Find "java/util/List" Class (Standard JAVA Class).
    jclass listClass = env->FindClass("java/util/List");
    if (listClass == NULL)
    {
        env->FatalError("Can't Find Class: java/util/List");
    }

    // Get "java.util.List.get(int location)" MethodID
    jmethodID listGetMethodID = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
    if (listGetMethodID == NULL)
    {
        env->FatalError("Can't GetMethodID for java.util.List.get(String)");
    }

    // Get "int java.util.List.size()" MethodID
    jmethodID listSizeMethodID = env->GetMethodID(listClass, "size", "()I");
    if (listSizeMethodID == NULL)
    {
        env->FatalError("Can't GetMethodID for String java.util.List.size()");
    }

    // String java.util.List.size()
    int listSize = (int)env->CallIntMethod(jpeersOjbect, listSizeMethodID);

    struct bcos_sdk_struct_endpoint* ep = (struct bcos_sdk_struct_endpoint*)malloc(
        listSize * sizeof(struct bcos_sdk_struct_endpoint));

    std::vector<bcos::boostssl::ws::EndPoint> endPoints;
    endPoints.resize(listSize);

    printf("peers has %i items\n", listSize);

    for (int i = 0; i < listSize; ++i)
    {
        // String java.util.List.get
        jstring jpeer = (jstring)env->CallObjectMethod(jpeersOjbect, listGetMethodID, i);
        if (jpeer == NULL)
        {
            env->FatalError("Can't CallObjectMethod(String java.util.List.get)");
        }

        const char* peer = env->GetStringUTFChars(jpeer, NULL);
        if (peer == NULL)
        {
            env->FatalError("Can't GetStringUTFChars(String java.util.List.get)");
        }

        if (!bcos::boostssl::ws::WsTools::stringToEndPoint(peer, endPoints[i]))
        {
            printf(" ## ==> index: %d, peer: %s\n", i, peer);
            env->FatalError("Not valid connected peer");
            continue;
        }
        else
        {
            ep[i].host = (char*)endPoints[i].host.c_str();
            ep[i].port = endPoints[i].port;
        }

        printf(" ## ==> index: %d, peer: %s\n", i, peer);
        env->ReleaseStringUTFChars(jpeer, peer);
    }

    // init bcos_sdk_struct_config
    struct bcos_sdk_struct_config config;
    config.heartbeat_period_ms = heartbeatPeriodMs;
    config.reconnect_period_ms = reconnectPeriodMs;
    config.message_timeout_ms = messageTimeoutMs;
    config.thread_pool_size = threadPoolSize;
    config.peers_count = listSize;
    config.peers = ep;

    // create rpc obj
    void* rpc = bcos_sdk_create_rpc(&config);
    // free ep
    free((void*)ep);
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
    void* rpc = obtain_rpc_obj(env, self);
    bcos_sdk_start_rpc(rpc);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_stop(JNIEnv* env, jobject self)
{
    void* rpc = obtain_rpc_obj(env, self);
    bcos_sdk_stop_rpc(rpc);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    call
 * Signature: (Ljava/lang/String;Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_call(
    JNIEnv* env, jobject self, jstring jto, jstring jdata, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // to
    const char* to = env->GetStringUTFChars(jto, NULL);
    // data
    const char* data = env->GetStringUTFChars(jdata, NULL);
    // TODO:
    bcos_rpc_call(rpc, group, to, data, NULL, NULL);

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
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* data = env->GetStringUTFChars(jdata, NULL);
    // proof
    int proof = (jproof == JNI_TRUE ? 1 : 0);
    // TODO:
    bcos_rpc_send_transaction(rpc, group, data, proof, NULL, NULL);

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
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* tx_hash = env->GetStringUTFChars(jtx_hash, NULL);
    // proof
    int proof = (jproof == JNI_TRUE ? 1 : 0);
    // TODO:
    bcos_rpc_get_transaction(rpc, group, tx_hash, proof, NULL, NULL);

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
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* tx_hash = env->GetStringUTFChars(jtx_hash, NULL);
    // proof
    int proof = (jproof == JNI_TRUE ? 1 : 0);
    // TODO:
    bcos_rpc_get_transaction_receipt(rpc, group, tx_hash, proof, NULL, NULL);

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
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* block_hash = env->GetStringUTFChars(jblock_hash, NULL);
    // only_header
    int only_header = (jonly_header == JNI_TRUE ? 1 : 0);
    // only_txhash
    int only_txhash = (jonly_txhash == JNI_TRUE ? 1 : 0);
    // TODO:
    bcos_rpc_get_block_by_hash(rpc, group, block_hash, only_header, only_txhash, NULL, NULL);

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
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // block number
    long block_number = reinterpret_cast<long>(jnumber);
    // only_header
    int only_header = (jonly_header == JNI_TRUE ? 1 : 0);
    // only_txhash
    int only_txhash = (jonly_txhash == JNI_TRUE ? 1 : 0);
    // TODO:
    bcos_rpc_get_block_by_number(rpc, group, block_number, only_header, only_txhash, NULL, NULL);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getBlockHashByNumber
 * Signature: (JLorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getBlockHashByNumber(
    JNIEnv* env, jobject self, jlong jnumber, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // block number
    long block_number = reinterpret_cast<long>(jnumber);
    // TODO:
    bcos_rpc_get_block_hash_by_number(rpc, group, block_number, NULL, NULL);
}


/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getBlockNumber
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getBlockNumber(
    JNIEnv* env, jobject self, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // TODO:
    bcos_rpc_get_block_number(rpc, group, handle_rpc_resp_cb, rpc);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getCode
 * Signature: (Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getCode(
    JNIEnv* env, jobject self, jstring jaddress, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* address = env->GetStringUTFChars(jaddress, NULL);
    // TODO:
    bcos_rpc_get_code(rpc, group, address, NULL, NULL);

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
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    bcos_rpc_get_sealer_list(rpc, group, NULL, NULL);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getObserverList
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getObserverList(
    JNIEnv* env, jobject self, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    bcos_rpc_get_observer_list(rpc, group, NULL, NULL);
}
/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getPbftView
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getPbftView(
    JNIEnv* env, jobject self, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    bcos_rpc_get_pbft_view(rpc, group, NULL, NULL);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getPendingTxSize
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getPendingTxSize(
    JNIEnv* env, jobject self, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    bcos_rpc_get_pending_tx_size(rpc, group, NULL, NULL);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getSyncStatus
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getSyncStatus(
    JNIEnv* env, jobject self, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    bcos_rpc_get_sync_status(rpc, group, NULL, NULL);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getSystemConfigByKey
 * Signature: (Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getSystemConfigByKey(
    JNIEnv* env, jobject self, jstring jkey, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();
    // data
    const char* key = env->GetStringUTFChars(jkey, NULL);
    // TODO:
    bcos_rpc_get_system_config_by_key(rpc, group, key, NULL, NULL);

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
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);
    // group
    std::string tempGroup = obtain_group_params(env, self);
    const char* group = tempGroup.c_str();

    bcos_rpc_get_total_transaction_count(rpc, group, NULL, NULL);
}


/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getPeers
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getPeers(
    JNIEnv* env, jobject self, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);

    bcos_rpc_get_peers(rpc, NULL, NULL);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_rpc_Rpc
 * Method:    getNodeInfo
 * Signature: (Lorg/fisco/bcos/sdk/jni/rpc/RpcCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_rpc_Rpc_getNodeInfo(
    JNIEnv* env, jobject self, jobject callback)
{
    std::ignore = callback;

    // rpc obj handler
    void* rpc = obtain_rpc_obj(env, self);

    bcos_rpc_get_node_info(rpc, NULL, NULL);
}
