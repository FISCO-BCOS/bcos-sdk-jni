#include "org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj.h"
#include "bcos-c-sdk/bcos_sdk_c_error.h"
#include "bcos-c-sdk/bcos_sdk_c_uti_keypair.h"
#include "bcos-c-sdk/bcos_sdk_c_uti_tx.h"
#include "org_fisco_bcos_sdk_exception.h"
#include <tuple>


/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    createDeployContractSignedTransaction
 * Signature:
 * (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_createDeployContractSignedTransaction(
    JNIEnv* env, jclass, jlong jkeypair, jstring jgroup_id, jstring jchain_id, jstring jcode,
    jstring jabi, jlong jblock_limit, jstring jtx_hash, jstring jsigned_tx)
{
    // keypair
    void* keypair = reinterpret_cast<void*>(jkeypair);
    // group id
    const char* group_id = env->GetStringUTFChars(jgroup_id, NULL);
    // chain id
    const char* chain_id = env->GetStringUTFChars(jchain_id, NULL);
    // code
    const char* code = env->GetStringUTFChars(jcode, NULL);
    // abi
    const char* abi = env->GetStringUTFChars(jabi, NULL);
    // block limit
    int64_t block_limit = (int64_t)jblock_limit;

    char* tx_hash = NULL;
    char* signed_tx = NULL;
    bcos_sdk_create_deploy_contract_signed_tx(
        keypair, group_id, chain_id, code, abi, block_limit, &tx_hash, &signed_tx);
    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    jstring jtx_hash_ret = env->NewStringUTF(tx_hash);
    jstring jsigned_tx_ret = env->NewStringUTF(signed_tx);

    // release resoure
    env->ReleaseStringUTFChars(jgroup_id, group_id);
    env->ReleaseStringUTFChars(jchain_id, chain_id);
    env->ReleaseStringUTFChars(jcode, code);
    env->ReleaseStringUTFChars(jabi, abi);
    // TODO: free tx_hash、 signed_tx

    jtx_hash = jtx_hash_ret;
    jsigned_tx = jsigned_tx_ret;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    createSignedTransaction
 * Signature:
 * (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JILjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL
Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_createSignedTransaction(
    JNIEnv* env, jclass, jlong jkeypair, jstring jgroup_id, jstring jchain_id, jstring jto,
    jstring jdata, jlong jblock_limit, jint jatti, jstring jtx_hash, jstring jsigned_tx)
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
    // block limit
    int64_t block_limit = (int64_t)jblock_limit;
    // atti
    int atti = (int)jatti;

    char* tx_hash = NULL;
    char* signed_tx = NULL;
    bcos_sdk_create_signed_tx(
        keypair, group_id, chain_id, to, data, block_limit, atti, &tx_hash, &signed_tx);
    if (!bcos_sdk_is_last_opr_success())
    {
        THROW_JNI_EXCEPTION(env, bcos_sdk_get_last_error_msg());
    }

    jstring jtx_hash_ret = env->NewStringUTF(tx_hash);
    jstring jsigned_tx_ret = env->NewStringUTF(signed_tx);

    // release resoure
    env->ReleaseStringUTFChars(jgroup_id, group_id);
    env->ReleaseStringUTFChars(jchain_id, chain_id);
    env->ReleaseStringUTFChars(jto, to);
    env->ReleaseStringUTFChars(jdata, data);
    // TODO: free tx_hash、 signed_tx

    jtx_hash = jtx_hash_ret;
    jsigned_tx = jsigned_tx_ret;
}
