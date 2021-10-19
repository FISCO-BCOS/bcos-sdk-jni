#include "jni/org_fisco_bcos_sdk_jni_amop_Amop.h"
#include "bcos_sdk_c.h"
#include "bcos_sdk_c_amop.h"
#include <tuple>

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    newNativeObj
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/JniConfig;)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_newNativeObj(
    JNIEnv* env, jclass, jobject)
{
    struct bcos_sdk_c_config config;
    // TODO: init config
    void* amop = bcos_sdk_create_amop(&config);
    if (amop == NULL)
    {
        // TODO: error handler
        env->FatalError("bcos_sdk_create_amop return NULL");
    }
    return reinterpret_cast<jlong>(amop);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_start(JNIEnv* env, jobject self)
{
    std::ignore = env;
    std::ignore = self;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_stop(JNIEnv* env, jobject self)
{
    std::ignore = env;
    std::ignore = self;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    subscribeTopic
 * Signature: (Ljava/util/Set;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_subscribeTopic__Ljava_util_Set_2(
    JNIEnv* env, jobject self, jobject topics)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = topics;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    subscribeTopic
 * Signature: (Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/amop/AmopCallback;)V
 */
JNIEXPORT void JNICALL
Java_org_fisco_bcos_sdk_jni_amop_Amop_subscribeTopic__Ljava_lang_String_2Lorg_fisco_bcos_sdk_jni_amop_AmopCallback_2(
    JNIEnv* env, jobject self, jstring topic, jobject callback)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = topic;
    std::ignore = callback;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    unsubscribeTopic
 * Signature: (Ljava/util/Set;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_unsubscribeTopic(
    JNIEnv* env, jobject self, jobject topics)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = topics;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    setCallback
 * Signature: (Lorg/fisco/bcos/sdk/jni/amop/AmopCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_setCallback(
    JNIEnv* env, jobject self, jobject callback)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = callback;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    getCallback
 * Signature: (Lorg/fisco/bcos/sdk/jni/amop/AmopCallback;)Lorg/fisco/bcos/sdk/jni/amop/AmopCallback;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_getCallback(
    JNIEnv* env, jobject self, jobject callback)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = callback;

    return jobject();
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    sendAmopMsg
 * Signature: ([BLorg/fisco/bcos/sdk/jni/amop/AmopResponseCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_sendAmopMsg(
    JNIEnv* env, jobject self, jbyteArray data, jobject callback)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = data;
    std::ignore = callback;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    broadcastAmopMsg
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_broadcastAmopMsg(
    JNIEnv* env, jobject self, jbyteArray data)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = data;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    getSubTopics
 * Signature: ()Ljava/util/Set;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_getSubTopics(
    JNIEnv* env, jobject self)
{
    std::ignore = env;
    std::ignore = self;

    return jobject();
}
