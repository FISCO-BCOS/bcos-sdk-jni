#include "jni/org_fisco_bcos_sdk_common.h"
#include "bcos_sdk_c_common.h"
#include <bcos-boostssl/websocket/WsTools.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <vector>

void* get_obj_native_member(JNIEnv* env, jobject self)
{
    jclass cls = env->GetObjectClass(self);
    if (!cls)
    {
        env->FatalError("Cannot GetObjectClass, get_obj_native_member");
    }

    jfieldID nativeFieldID = env->GetFieldID(cls, "nativeObj", "J");
    if (!nativeFieldID)
    {
        env->FatalError("Cannot GetFieldID, get_obj_native_member");
    }

    jlong nativeObj = env->GetLongField(self, nativeFieldID);
    void* native = reinterpret_cast<void*>(nativeObj);
    if (native == NULL)
    {
        env->FatalError("Cannot GetFieldID, get_obj_native_member");
    }

    return native;
}

static bcos_sdk_c_cert_config* create_bcos_sdk_c_cert_config(
    JNIEnv* env, jclass certConfigClass, jobject jCertConfig)
{
    /*
    public static class CertConfig {
        private String caCert;
        private String nodeKey;
        private String nodeCert;
    }
    */
    jfieldID caCertField = env->GetFieldID(certConfigClass, "caCert", "Ljava/lang/String;");
    if (caCertField == NULL)
    {
        env->FatalError("Cannot GetFieldID for caCert of CertConfig");
    }
    jstring jCaCert = (jstring)env->GetObjectField(jCertConfig, caCertField);
    const char* caCert = jCaCert ? env->GetStringUTFChars(jCaCert, NULL) : NULL;

    jfieldID nodeKeyField = env->GetFieldID(certConfigClass, "nodeKey", "Ljava/lang/String;");
    if (nodeKeyField == NULL)
    {
        env->FatalError("Cannot GetFieldID for nodeKey of CertConfig");
    }
    jstring jNodeKey = (jstring)env->GetObjectField(jCertConfig, nodeKeyField);
    const char* nodeKey = jNodeKey ? env->GetStringUTFChars(jNodeKey, NULL) : NULL;

    jfieldID nodeCertField = env->GetFieldID(certConfigClass, "nodeCert", "Ljava/lang/String;");
    if (nodeCertField == NULL)
    {
        env->FatalError("Cannot GetFieldID for nodeCert of CertConfig");
    }
    jstring jNodeCert = (jstring)env->GetObjectField(jCertConfig, nodeCertField);
    const char* nodeCert = jNodeCert ? env->GetStringUTFChars(jNodeCert, NULL) : NULL;

    struct bcos_sdk_c_cert_config* config =
        (struct bcos_sdk_c_cert_config*)malloc(sizeof(struct bcos_sdk_c_cert_config));

    config->ca_cert = caCert ? strdup(caCert) : NULL;
    config->node_cert = nodeCert ? strdup(nodeCert) : NULL;
    config->node_key = nodeKey ? strdup(nodeKey) : NULL;

    printf("[create_bcos_sdk_c_cert_config] ==>>ca cert: %s, node cert: %s, node key: %s \n",
        config->ca_cert, config->node_cert, config->node_key);

    if (caCert)
    {
        env->ReleaseStringUTFChars(jCaCert, caCert);
    }
    if (nodeKey)
    {
        env->ReleaseStringUTFChars(jNodeKey, nodeKey);
    }
    if (nodeCert)
    {
        env->ReleaseStringUTFChars(jNodeCert, nodeCert);
    }

    return config;
}

static bcos_sdk_c_sm_cert_config* create_bcos_sdk_c_sm_cert_config(
    JNIEnv* env, jclass smCertConfigClass, jobject jSmCertConfig)
{
    /*
    public static class SMCertConfig {
        private String caCert;
        private String nodeCert;
        private String nodeKey;
        private String enNodeCert;
        private String enNodeKey;
    */
    // caCert
    jfieldID caCertField = env->GetFieldID(smCertConfigClass, "caCert", "Ljava/lang/String;");
    if (caCertField == NULL)
    {
        env->FatalError("Cannot GetFieldID for caCert of SMCertConfig");
    }
    jstring jCaCert = (jstring)env->GetObjectField(jSmCertConfig, caCertField);
    const char* caCert = jCaCert ? env->GetStringUTFChars(jCaCert, NULL) : NULL;

    // nodeCert
    jfieldID nodeCertField = env->GetFieldID(smCertConfigClass, "nodeCert", "Ljava/lang/String;");
    if (nodeCertField == NULL)
    {
        env->FatalError("Cannot GetFieldID for nodeCert of SMCertConfig");
    }
    jstring jNodeCert = (jstring)env->GetObjectField(jSmCertConfig, nodeCertField);
    const char* nodeCert = jNodeCert ? env->GetStringUTFChars(jNodeCert, NULL) : NULL;

    // nodeKey
    jfieldID nodeKeyField = env->GetFieldID(smCertConfigClass, "nodeKey", "Ljava/lang/String;");
    if (nodeKeyField == NULL)
    {
        env->FatalError("Cannot GetFieldID for nodeKey of SMCertConfig");
    }
    jstring jNodeKey = (jstring)env->GetObjectField(jSmCertConfig, nodeKeyField);
    const char* nodeKey = jNodeKey ? env->GetStringUTFChars(jNodeKey, NULL) : NULL;

    // enNodeCert
    jfieldID enNodeCertField =
        env->GetFieldID(smCertConfigClass, "enNodeCert", "Ljava/lang/String;");
    if (enNodeCertField == NULL)
    {
        env->FatalError("Cannot GetFieldID for enNodeCert of SMCertConfig");
    }
    jstring jEnNodeCert = (jstring)env->GetObjectField(jSmCertConfig, enNodeCertField);
    const char* enNodeCert = jEnNodeCert ? env->GetStringUTFChars(jEnNodeCert, NULL) : NULL;

    // enNodeKey
    jfieldID enNodeKeyField = env->GetFieldID(smCertConfigClass, "enNodeKey", "Ljava/lang/String;");
    if (enNodeKeyField == NULL)
    {
        env->FatalError("Cannot GetFieldID for enNodeCert of SMCertConfig");
    }
    jstring jEnNodeKey = (jstring)env->GetObjectField(jSmCertConfig, enNodeKeyField);
    const char* enNodeKey = jEnNodeKey ? env->GetStringUTFChars(jEnNodeKey, NULL) : NULL;

    struct bcos_sdk_c_sm_cert_config* config =
        (struct bcos_sdk_c_sm_cert_config*)malloc(sizeof(struct bcos_sdk_c_sm_cert_config));

    config->ca_cert = caCert ? strdup(caCert) : NULL;
    config->node_cert = nodeCert ? strdup(nodeCert) : NULL;
    config->node_key = nodeKey ? strdup(nodeKey) : NULL;
    config->en_node_cert = enNodeCert ? strdup(enNodeCert) : NULL;
    config->en_node_key = enNodeKey ? strdup(enNodeKey) : NULL;

#if defined(_BCOS_SDK_JNI_DEBUG_)
    printf(
        "[create_bcos_sdk_c_sm_cert_config] ==>>ca cert: %s, node cert: %s, node key: %s, en node "
        "cert: %s, en node key:%s \n",
        config->ca_cert, config->node_cert, config->node_key, config->en_node_cert,
        config->en_node_key);
#endif

    if (caCert)
    {
        env->ReleaseStringUTFChars(jCaCert, caCert);
    }
    if (nodeKey)
    {
        env->ReleaseStringUTFChars(jNodeKey, nodeKey);
    }
    if (nodeCert)
    {
        env->ReleaseStringUTFChars(jNodeCert, nodeCert);
    }
    if (enNodeKey)
    {
        env->ReleaseStringUTFChars(jEnNodeKey, enNodeKey);
    }
    if (enNodeCert)
    {
        env->ReleaseStringUTFChars(jEnNodeCert, enNodeCert);
    }

    return config;
}

struct bcos_sdk_c_config* create_bcos_sdk_c_config_from_java_obj(JNIEnv* env, jobject jconfig)
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
    {  // TODO: jpeersOjbect will be null if peer is empty, how to fix.
        env->FatalError("Cannot GetObjectField for peers of JniConfig");
    }

    // Find "java/util/List" Class (Standard JAVA Class).
    jclass listClass = env->FindClass("java/util/List");
    if (listClass == NULL)
    {
        env->FatalError("Cannot Find Class: java/util/List");
    }

    // Get "java.util.List.get(int location)" MethodID
    jmethodID listGetMethodID = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
    if (listGetMethodID == NULL)
    {
        env->FatalError("Cannot GetMethodID for java.util.List.get(String)");
    }

    // Get "int java.util.List.size()" MethodID
    jmethodID listSizeMethodID = env->GetMethodID(listClass, "size", "()I");
    if (listSizeMethodID == NULL)
    {
        env->FatalError("Cannot GetMethodID for String java.util.List.size()");
    }

    // String java.util.List.size()
    int listSize = (int)env->CallIntMethod(jpeersOjbect, listSizeMethodID);

    // Note: ep should be free after bcos_sdk_c_config out of use
    struct bcos_sdk_c_endpoint* ep =
        (struct bcos_sdk_c_endpoint*)malloc(listSize * sizeof(struct bcos_sdk_c_endpoint));

    for (int i = 0; i < listSize; ++i)
    {
        // String java.util.List.get
        jstring jpeer = (jstring)env->CallObjectMethod(jpeersOjbect, listGetMethodID, i);
        if (jpeer == NULL)
        {
            env->FatalError("Cannot CallObjectMethod(String java.util.List.get)");
        }

        const char* peer = env->GetStringUTFChars(jpeer, NULL);
        if (peer == NULL)
        {
            env->FatalError("Cannot GetStringUTFChars(String java.util.List.get)");
        }

        bcos::boostssl::ws::EndPoint endPoint;
        if (!bcos::boostssl::ws::WsTools::stringToEndPoint(peer, endPoint))
        {
            env->FatalError("Not valid connected peer");
            continue;
        }
        else
        {
            ep[i].host = strdup(endPoint.host.c_str());
            ep[i].port = endPoint.port;
        }

        env->ReleaseStringUTFChars(jpeer, peer);
    }

    // add ssl impl
    jfieldID jdisableSsl = env->GetFieldID(configClass, "disableSsl", "Z");

    bool disableSsl = (int)env->GetBooleanField(jconfig, jdisableSsl);

    bcos_sdk_c_cert_config* cert_config = NULL;
    bcos_sdk_c_sm_cert_config* sm_cert_config = NULL;
    if (!disableSsl)
    {
        {
            jfieldID certConfigField = env->GetFieldID(
                configClass, "certConfig", "Lorg/fisco/bcos/sdk/jni/common/JniConfig$CertConfig;");
            if (certConfigField == NULL)
            {  // TODO: jcertConfig will be null if peer is empty, how to fix.
                env->FatalError("Cannot GetFieldID for certConfig of JniConfig");
            }

            jobject jcertConfig = env->GetObjectField(jconfig, certConfigField);
            if (jcertConfig == NULL)
            {  // TODO: jcertConfig will be null if peer is empty, how to fix.
                env->FatalError("Cannot GetObjectField for certConfig of JniConfig");
            }

            jclass certConfigClass = env->GetObjectClass(jcertConfig);
            cert_config = create_bcos_sdk_c_cert_config(env, certConfigClass, jcertConfig);
        }

        {
            jfieldID smCertConfigField = env->GetFieldID(configClass, "smCertConfig",
                "Lorg/fisco/bcos/sdk/jni/common/JniConfig$SMCertConfig;");
            jobject jSmCertConfig = env->GetObjectField(jconfig, smCertConfigField);
            if (jSmCertConfig == NULL)
            {  // TODO: jcertConfig will be null if peer is empty, how to fix.
                env->FatalError("Cannot GetObjectField for smCertConfig of JniConfig");
            }

            jclass smCertConfigClass = env->GetObjectClass(jSmCertConfig);
            sm_cert_config =
                create_bcos_sdk_c_sm_cert_config(env, smCertConfigClass, jSmCertConfig);
        }
    }

    struct bcos_sdk_c_config* config = bcos_sdk_c_config_create();
    // init bcos_sdk_c_config
    config->heartbeat_period_ms = heartbeatPeriodMs;
    config->reconnect_period_ms = reconnectPeriodMs;
    config->message_timeout_ms = messageTimeoutMs;
    config->thread_pool_size = threadPoolSize;
    config->peers_count = listSize;
    config->disableSsl = disableSsl;
    config->peers = ep;
    config->cert_config = cert_config;
    config->sm_cert_config = sm_cert_config;

    return config;
}