package org.fisco.bcos.sdk.jni.utilities.tx;

import org.fisco.bcos.sdk.jni.common.JniException;
import org.fisco.bcos.sdk.jni.common.JniLibLoader;

public class TransactionBuilderJniObj {

  static {
    JniLibLoader.loadJniLibrary();
  }

  /**
   * @param groupID
   * @param chainID
   * @param to
   * @param data
   * @param abi
   * @param blockLimit
   * @return
   */
  public static native long createTransactionData(
      String groupID, String chainID, String to, String data, String abi, long blockLimit)
      throws JniException;

  /** @param transactionData */
  public static native void destroyTransactionData(long transactionData)
      throws JniException;

  /**
   * @param transactionData
   * @return
   */
  public static native String encodeTransactionData(long transactionData)
      throws JniException;

  /**
   * @param cryptoType
   * @param transactionData
   * @return
   */
  public static native String calcTransactionDataHash(
      int cryptoType, long transactionData) throws JniException;

  /**
   * @param keyPair
   * @param transactionDataHash
   * @return
   */
  public static native String signTransactionDataHash(
      long keyPair, String transactionDataHash) throws JniException;

  /**
   * @param transactionData
   * @param transactionDataHashSignedData
   * @param transactionDataHash
   * @param attribute
   * @return
   */
  public static native String createSignedTransaction(
      long transactionData,
      String transactionDataHashSignedData,
      String transactionDataHash,
      int attribute)
      throws JniException;

  /**
   * @param keyPair
   * @param groupID
   * @param chainID
   * @param to
   * @param data
   * @param blockLimit
   * @param attribute
   * @return
   * @throws JniException
   */
  public static native TxPair createSignedTransaction(
      long keyPair,
      String groupID,
      String chainID,
      String to,
      String data,
      String abi,
      long blockLimit,
      int attribute)
      throws JniException;
}
