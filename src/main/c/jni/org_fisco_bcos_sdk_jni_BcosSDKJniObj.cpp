
#include "jni/org_fisco_bcos_sdk_jni_BcosSDKJniObj.h"
#include "bcos-c-sdk/bcos_sdk_c.h"
#include "bcos-c-sdk/bcos_sdk_c_error.h"
#include "jni/org_fisco_bcos_sdk_common.h"
#include <tuple>

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDKJniObj
 * Method:    create
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/JniConfig;)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDKJniObj_create(
    JNIEnv* env, jclass self, jobject jconfig)
{
    (void)self;
    // config
    struct bcos_sdk_c_config* config = create_config_from_java_obj(env, jconfig);
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
 * Class:     org_fisco_bcos_sdk_jni_BcosSDKJniObj
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDKJniObj_start(JNIEnv* env, jobject self)
{
    void* sdk = bcos_sdk_get_native_pointer(env, self);
    if (sdk)
    {
        bcos_sdk_start(sdk);
    }
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDKJniObj
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDKJniObj_stop(JNIEnv* env, jobject self)
{
    void* sdk = bcos_sdk_get_native_pointer(env, self);
    if (sdk)
    {
        bcos_sdk_stop(sdk);
    }
}

/*
 * Class:     org_fisco_bcos_sdk_jni_BcosSDKJniObj
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_BcosSDKJniObj_destroy(JNIEnv* env, jobject self)
{
    void* sdk = bcos_sdk_get_native_pointer(env, self);
    if (sdk)
    {
        bcos_sdk_destroy(sdk);
    }
}