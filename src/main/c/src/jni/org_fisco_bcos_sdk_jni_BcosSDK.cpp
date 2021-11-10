
#include "jni/org_fisco_bcos_sdk_jni_BcosSDK.h"
#include "bcos_sdk_c.h"
#include "bcos_sdk_c_error.h"
#include "jni/org_fisco_bcos_sdk_common.h"
#include <tuple>

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    newNativeObj
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/JniConfig;)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_newNativeObj(
    JNIEnv* env, jclass, jobject jconfig)
{
    // config
    struct bcos_sdk_c_config* config = create_bcos_sdk_c_config_from_java_obj(env, jconfig);
    // create sdk obj
    void* sdk = bcos_sdk_create(config);
    // destroy config
    bcos_sdk_c_config_destroy(config);
    if (bcos_sdk_get_last_error() == 0)
    {
        return reinterpret_cast<jlong>(sdk);
    }

    // throw exception in java
    THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());

    return 0;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    getRpcNativeObj
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_getRpcNativeObj(
    JNIEnv* env, jobject self)
{
    void* sdk = get_obj_native_member(env, self);
    if (sdk)
    {
        return reinterpret_cast<jlong>(bcos_sdk_get_rpc(sdk));
    }

    return 0;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    getAmopNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_getAmopNative(JNIEnv* env, jclass self)
{
    void* sdk = get_obj_native_member(env, self);
    if (sdk)
    {
        return reinterpret_cast<jlong>(bcos_sdk_get_amop(sdk));
    }

    return 0;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    getEventSubNative
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_getEventSubNative(
    JNIEnv* env, jobject self)
{
    void* sdk = get_obj_native_member(env, self);
    if (sdk)
    {
        return reinterpret_cast<jlong>(bcos_sdk_get_event_sub(sdk));
    }

    return 0;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_destroy(JNIEnv* env, jobject self)
{
    void* sdk = get_obj_native_member(env, self);
    if (sdk)
    {
        bcos_sdk_destroy(sdk);
    }
}