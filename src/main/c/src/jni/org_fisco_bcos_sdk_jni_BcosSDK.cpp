
#include "jni/org_fisco_bcos_sdk_jni_BcosSDK.h"
#include <tuple>
/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    newNativeObj
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/JniConfig;)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_newNativeObj(JNIEnv*, jclass, jobject)
{
    return 0;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    build
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/JniConfig;)Lorg/fisco/bcos/sdk/jni/BcosSDK;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_build(JNIEnv*, jclass, jobject)
{
    return jobject();
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    getRpc
 * Signature: (Ljava/lang/String;)Lorg/fisco/bcos/sdk/jni/rpc/Rpc;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_getRpc(JNIEnv*, jobject, jstring)
{
    return jobject();
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    getAmop
 * Signature: ()Lorg/fisco/bcos/sdk/jni/amop/Amop;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_getAmop(JNIEnv*, jobject)
{
    return jobject();
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    getEventSubscribe
 * Signature: (Ljava/lang/String;)Lorg/fisco/bcos/sdk/jni/event/EventSubscribe;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_getEventSubscribe(
    JNIEnv*, jobject, jstring)
{
    return jobject();
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    stopAll
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_stopAll(JNIEnv*, jobject)
{
    return;
}
