#include "org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj.h"
#include "bcos-c-sdk/bcos_sdk_c_error.h"
#include "bcos-c-sdk/bcos_sdk_c_uti_keypair.h"
#include "bcos-c-sdk/bcos_sdk_c_uti_tx.h"
#include "org_fisco_bcos_sdk_exception.h"
#include <tuple>

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    createTransactionData
 * Signature:
 * (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;J)J
 */
JNIEXPORT jlong JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_createTransactionData(JNIEnv* env,
    jclass, jstring jgroup_id, jstring jchain_id, jstring jto, jstring jdata, jstring jabi,
    jlong jblock_limit)
{
    // group id
    const char* group_id = env->GetStringUTFChars(jgroup_id, NULL);
    // chain id
    const char* chain_id = env->GetStringUTFChars(jchain_id, NULL);
    // code
    const char* to = env->GetStringUTFChars(jto, NULL);
    // data
    const char* data = env->GetStringUTFChars(jdata, NULL);
    // abi
    const char* abi = env->GetStringUTFChars(jabi, NULL);
    // block limit
    int64_t block_limit = (int64_t)jblock_limit;

    void* transaction_data =
        bcos_sdk_create_transaction_data(group_id, chain_id, to, data, abi, block_limit);

    env->ReleaseStringUTFChars(jgroup_id, group_id);
    env->ReleaseStringUTFChars(jchain_id, chain_id);
    env->ReleaseStringUTFChars(jto, to);
    env->ReleaseStringUTFChars(jdata, data);
    env->ReleaseStringUTFChars(jabi, abi);

    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    return reinterpret_cast<jlong>(transaction_data);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    destroyTransactionData
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_destroyTransactionData(
    JNIEnv*, jclass, jlong jtransaction_data)
{
    void* transaction_data = reinterpret_cast<void*>(jtransaction_data);
    bcos_sdk_destroy_transaction_data(transaction_data);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    encodeTransactionData
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_encodeTransactionData(
    JNIEnv* env, jclass, jlong jtransaction_data)
{
    void* transaction_data = reinterpret_cast<void*>(jtransaction_data);
    const char* encoded_transaction_data = bcos_sdk_encode_transaction_data(transaction_data);
    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    jstring jencoded_transaction_data = env->NewStringUTF(encoded_transaction_data);
    return jencoded_transaction_data;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    calcTransactionDataHash
 * Signature: (IJ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_calcTransactionDataHash(
    JNIEnv* env, jclass, jint jcrypto_type, jlong jtransaction_data)
{
    void* transaction_data = reinterpret_cast<void*>(jtransaction_data);
    int crypto_type = jcrypto_type;
    const char* transaction_data_hash =
        bcos_sdk_calc_transaction_data_hash(crypto_type, transaction_data);
    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    jstring jtransaction_data_hash = env->NewStringUTF(transaction_data_hash);
    return jtransaction_data_hash;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    signTransactionDataHash
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_signTransactionDataHash(
    JNIEnv* env, jclass, jlong jkeypair, jstring jtransaction_data_hash)
{
    //
    void* keypair = reinterpret_cast<void*>(jkeypair);
    // transaction_data_hash
    const char* transaction_data_hash = env->GetStringUTFChars(jtransaction_data_hash, NULL);

    const char* signed_data = bcos_sdk_sign_transaction_data_hash(keypair, transaction_data_hash);

    env->ReleaseStringUTFChars(jtransaction_data_hash, transaction_data_hash);

    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    jstring jsigned_data = env->NewStringUTF(signed_data);
    return jsigned_data;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    createSignedTransaction
 * Signature: (JLjava/lang/String;Ljava/lang/String;I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_createSignedTransaction__JLjava_lang_String_2Ljava_lang_String_2I(
    JNIEnv* env, jclass, jlong jtransaction_data, jstring jtransaction_data_signed_data,
    jstring jtransaction_data_hash, jint jattr)
{
    void* transaction_data = reinterpret_cast<void*>(jtransaction_data);

    const char* transaction_data_signed_data =
        env->GetStringUTFChars(jtransaction_data_signed_data, NULL);
    const char* transaction_data_hash = env->GetStringUTFChars(jtransaction_data_hash, NULL);
    int attr = jattr;

    const char* signed_tx = bcos_sdk_create_signed_transaction_with_signed_data(
        transaction_data, transaction_data_signed_data, transaction_data_hash, attr);

    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    jstring jsigned_tx = env->NewStringUTF(signed_tx);
    return jsigned_tx;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    createSignedTransaction
 * Signature:
 * (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JI)Lorg/fisco/bcos/sdk/jni/utilities/tx/TxPair;
 */
JNIEXPORT jobject JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_createSignedTransaction__JLjava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2JI(
    JNIEnv* env, jclass, jlong jkeypair, jstring jgroup_id, jstring jchain_id, jstring jto,
    jstring jdata, jstring jabi, jlong jblock_limit, jint jattr)
{
    // keypair
    void* keypair = reinterpret_cast<void*>(jkeypair);
    // group id
    const char* group_id = env->GetStringUTFChars(jgroup_id, NULL);
    // chain id
    const char* chain_id = env->GetStringUTFChars(jchain_id, NULL);
    // to
    const char* to = env->GetStringUTFChars(jto, NULL);
    // data
    const char* data = env->GetStringUTFChars(jdata, NULL);
    // abi
    const char* abi = env->GetStringUTFChars(jabi, NULL);
    // block limit
    int64_t block_limit = (int64_t)jblock_limit;
    // attr
    int attr = (int64_t)jattr;

    char* tx_hash = NULL;
    char* signed_tx = NULL;
    bcos_sdk_create_signed_transaction(
        keypair, group_id, chain_id, to, data, abi, block_limit, attr, &tx_hash, &signed_tx);
    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    jstring jtx_hash = env->NewStringUTF(tx_hash);
    jstring jsigned_tx = env->NewStringUTF(signed_tx);

    jclass jtxpair = env->FindClass("org/fisco/bcos/sdk/jni/utilities/tx/TxPair");
    if (jtxpair == NULL)
    {
        env->FatalError(
            "No such class, className: "
            "org/fisco/bcos/sdk/jni/utilities/tx/TxPair");
    }

    jmethodID txpair_mtd =
        env->GetMethodID(jtxpair, "<init>", "(Ljava/lang/String;Ljava/lang/String;)V");
    if (txpair_mtd == NULL)
    {
        env->FatalError("No such constructor in TxPair, constructor(String, String)");
    }

    jobject txpair = env->NewObject(jtxpair, txpair_mtd, jtx_hash, jsigned_tx);

    // release resoure
    env->ReleaseStringUTFChars(jgroup_id, group_id);
    env->ReleaseStringUTFChars(jchain_id, chain_id);
    env->ReleaseStringUTFChars(jdata, data);
    env->ReleaseStringUTFChars(jto, to);
    env->ReleaseStringUTFChars(jabi, abi);

    env->DeleteLocalRef(jtx_hash);
    env->DeleteLocalRef(jsigned_tx);
    // TODO: free tx_hash、 signed_tx

    return txpair;
}