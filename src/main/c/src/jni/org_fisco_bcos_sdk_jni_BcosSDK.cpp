
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
    catch (const bcos::BcosJniException& _e)
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
 * Method:    getRpc
 * Signature: (Ljava/lang/String;)Lorg/fisco/bcos/sdk/jni/rpc/Rpc;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_getRpc(
    JNIEnv* env, jobject self, jstring jgroup)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = jgroup;

    return jobject();
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    getAmop
 * Signature: ()Lorg/fisco/bcos/sdk/jni/amop/Amop;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_getAmop(JNIEnv* env, jobject self)
{
    std::ignore = env;
    std::ignore = self;

    return jobject();
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    getEventSubscribe
 * Signature: (Ljava/lang/String;)Lorg/fisco/bcos/sdk/jni/event/EventSubscribe;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_getEventSubscribe(
    JNIEnv* env, jobject self, jstring jgroup)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = jgroup;

    return jobject();
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDK
 * Method:    finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDK_finalize(JNIEnv* env, jobject self)
{
    void* sdk = get_obj_native_member(env, self);
    bcos_sdk_stop(sdk);
    bcos_sdk_destroy(sdk);
}