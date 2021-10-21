#include "jni/common.h"
#include "bcos_sdk_c_common.h"
#include <bcos-boostssl/websocket/WsTools.h>
#include <stdlib.h>
#include <vector>

void* obtain_native_object(JNIEnv* env, jobject self)
{
    jclass cls = env->GetObjectClass(self);
    if (!cls)
    {
        env->FatalError("Cannot  GetObjectClass, obtain_native_object");
    }

    jfieldID nativeFieldID = env->GetFieldID(cls, "nativeObj", "J");
    if (!nativeFieldID)
    {
        env->FatalError("Cannot  GetFieldID, obtain_native_object");
    }

    jlong nativeObj = env->GetLongField(self, nativeFieldID);
    void* rpc = reinterpret_cast<void*>(nativeObj);
    if (rpc == NULL)
    {
        env->FatalError("Cannot  GetFieldID, obtain_native_object");
    }

    return rpc;
}

struct bcos_sdk_c_config* init_bcos_sdk_c_config(JNIEnv* env, jobject jconfig)
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
        env->FatalError("Cannot  GetObjectField for peers of JniConfig");
    }

    // Find "java/util/List" Class (Standard JAVA Class).
    jclass listClass = env->FindClass("java/util/List");
    if (listClass == NULL)
    {
        env->FatalError("Cannot  Find Class: java/util/List");
    }

    // Get "java.util.List.get(int location)" MethodID
    jmethodID listGetMethodID = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
    if (listGetMethodID == NULL)
    {
        env->FatalError("Cannot  GetMethodID for java.util.List.get(String)");
    }

    // Get "int java.util.List.size()" MethodID
    jmethodID listSizeMethodID = env->GetMethodID(listClass, "size", "()I");
    if (listSizeMethodID == NULL)
    {
        env->FatalError("Cannot  GetMethodID for String java.util.List.size()");
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
            env->FatalError("Cannot  CallObjectMethod(String java.util.List.get)");
        }

        const char* peer = env->GetStringUTFChars(jpeer, NULL);
        if (peer == NULL)
        {
            env->FatalError("Cannot  GetStringUTFChars(String java.util.List.get)");
        }

        bcos::boostssl::ws::EndPoint endPoint;
        if (!bcos::boostssl::ws::WsTools::stringToEndPoint(peer, endPoint))
        {
            printf(" ## ==> index: %d, peer: %s\n", i, peer);
            env->FatalError("Not valid connected peer");
            continue;
        }
        else
        {
            ep[i].host = strdup(endPoint.host.c_str());
            ep[i].port = endPoint.port;
        }

        printf(" ## ==> index: %d, peer: %s\n", i, peer);
        env->ReleaseStringUTFChars(jpeer, peer);
    }

    struct bcos_sdk_c_config* config = bcos_sdk_c_config_new();
    // init bcos_sdk_c_config
    config->heartbeat_period_ms = heartbeatPeriodMs;
    config->reconnect_period_ms = reconnectPeriodMs;
    config->message_timeout_ms = messageTimeoutMs;
    config->thread_pool_size = threadPoolSize;
    config->peers_count = listSize;
    config->peers = ep;

    return config;
}