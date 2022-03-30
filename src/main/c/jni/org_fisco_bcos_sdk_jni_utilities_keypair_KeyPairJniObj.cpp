#include "org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj.h"
#include "bcos-c-sdk/bcos_sdk_c_error.h"
#include "bcos-c-sdk/bcos_sdk_c_uti_keypair.h"
#include "org_fisco_bcos_sdk_exception.h"
#include <tuple>

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj
 * Method:    createJniKeyPair
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj_createJniKeyPair__I(
    JNIEnv* env, jclass, jint jcrypto_type)
{
    int crypto_type = (int)jcrypto_type;
    void* keypair = bcos_sdk_create_keypair(crypto_type);

    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    return reinterpret_cast<jlong>(keypair);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj
 * Method:    createJniKeyPair
 * Signature: (I[B)J
 */
JNIEXPORT jlong JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj_createJniKeyPair__I_3B(
    JNIEnv* env, jclass, jint jcrypto_type, jbyteArray jdata)
{
    int crypto_type = (int)jcrypto_type;
    jbyte* data = (jbyte*)env->GetByteArrayElements(jdata, 0);
    jsize len = env->GetArrayLength(jdata);
    void* keypair = bcos_sdk_create_keypair_by_prikey(crypto_type, (void*)data, len);

    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    return reinterpret_cast<jlong>(keypair);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj
 * Method:    getJniKeyPairAddress
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj_getJniKeyPairAddress(
    JNIEnv* env, jclass, jlong jkeypair)
{
    void* keypair = reinterpret_cast<void*>(jkeypair);
    const char* addr = bcos_sdk_get_keypair_address(keypair);

    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    jstring result = env->NewStringUTF(addr);
    free((void*)addr);
    return result;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj
 * Method:    getJniKeyPairPubKey
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj_getJniKeyPairPubKey(
    JNIEnv* env, jclass, jlong jkeypair)
{
    void* keypair = reinterpret_cast<void*>(jkeypair);
    const char* pub = bcos_sdk_get_keypair_public_key(keypair);

    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    jstring result = env->NewStringUTF(pub);
    free((void*)pub);
    return result;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj
 * Method:    getJniKeyPairPrivateKey
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj_getJniKeyPairPrivateKey(
    JNIEnv* env, jclass, jlong jkeypair)
{
    void* keypair = reinterpret_cast<void*>(jkeypair);
    const char* pri = bcos_sdk_get_keypair_private_key(keypair);

    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    jstring result = env->NewStringUTF(pri);
    free((void*)pri);
    return result;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj
 * Method:    getJniKeyPairCryptoType
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj_getJniKeyPairCryptoType(
    JNIEnv* env, jclass, jlong jkeypair)
{
    void* key_pair = reinterpret_cast<void*>(jkeypair);
    int crypto_type = bcos_sdk_get_keypair_type(key_pair);

    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    return crypto_type;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj
 * Method:    destroyJniKeyPair
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_keypair_KeyPairJniObj_destroyJniKeyPair(
    JNIEnv*, jclass, jlong jkeypair)
{
    void* key_pair = reinterpret_cast<void*>(jkeypair);
    bcos_sdk_destroy_keypair(key_pair);
}