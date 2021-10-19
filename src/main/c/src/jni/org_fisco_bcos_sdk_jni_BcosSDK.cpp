
#include "jni/org_fisco_bcos_sdk_jni_BcosSDK.h"
#include <tuple>
/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    newNativeObj
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/JniConfig;)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_newNativeObj(
    JNIEnv* env, jclass cls, jobject config)
{
    std::ignore = env;
    std::ignore = cls;
    std::ignore = config;

    return 0;
}
