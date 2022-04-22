/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj */

#ifndef _Included_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
#define _Included_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    createTransactionData
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;J)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_createTransactionData
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jstring, jlong);

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    destroyTransactionData
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_destroyTransactionData
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    encodeTransactionData
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_encodeTransactionData
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    calcTransactionDataHash
 * Signature: (IJ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_calcTransactionDataHash
  (JNIEnv *, jclass, jint, jlong);

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    signTransactionDataHash
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_signTransactionDataHash
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    createSignedTransaction
 * Signature: (JLjava/lang/String;Ljava/lang/String;I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_createSignedTransaction__JLjava_lang_String_2Ljava_lang_String_2I
  (JNIEnv *, jclass, jlong, jstring, jstring, jint);

/*
 * Class:     org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj
 * Method:    createSignedTransaction
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;JI)Lorg/fisco/bcos/sdk/jni/utilities/tx/TxPair;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_utilities_tx_TransactionBuilderJniObj_createSignedTransaction__JLjava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2Ljava_lang_String_2JI
  (JNIEnv *, jclass, jlong, jstring, jstring, jstring, jstring, jstring, jlong, jint);

#ifdef __cplusplus
}
#endif
#endif
