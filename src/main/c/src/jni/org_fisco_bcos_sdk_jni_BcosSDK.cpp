
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
    // config
    struct bcos_sdk_c_config* config = create_bcos_sdk_c_config_from_java_obj(env, jconfig);
    // create sdk obj
    void* sdk = bcos_sdk_create(config);
    // destroy config
    bcos_sdk_c_config_destroy(config);
    if (sdk == NULL)
    {
        // TODO: how to handler the error
        env->FatalError("bcos_sdk_create return NULL");
    }

    return reinterpret_cast<jlong>(sdk);
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