
#include "jni/org_fisco_bcos_sdk_jni_BcosSDK.h"
#include "bcos_sdk_c.h"
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
    try
    {
        // config
        struct bcos_sdk_c_config* config = create_bcos_sdk_c_config_from_java_obj(env, jconfig);
        // create sdk obj
        void* sdk = bcos_sdk_create(config);
        // destroy config
        bcos_sdk_c_config_destroy(config);

        return reinterpret_cast<jlong>(sdk);
    }
    catch (const std::exception& _e)
    {
        BCOS_LOG(INFO) << LOG_BADGE("Java_org_fisco_bcos_sdk_jni_BcosSDK_newNativeObj")
                       << LOG_DESC("create bcos sdk native obj failed")
                       << LOG_KV("e", boost::diagnostic_information(_e));
        THROW_JNI_EXCEPTION(env, boost::diagnostic_information(_e));
    }
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