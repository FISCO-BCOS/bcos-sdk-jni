package org.fisco.bcos.sdk.jni.utilities.tx;

import org.fisco.bcos.sdk.jni.common.JniException;
import org.fisco.bcos.sdk.jni.common.JniLibLoader;

public class TransactionBuilderJniObj {

  static {
    JniLibLoader.loadJniLibrary();
  }

  /**
   * @param keypair
   * @param groupID
   * @param chainID
   * @param code
   * @param abi
   * @param blockLimit
   * @return
   * @throws JniException
   */
  public static native TxPair createDeployContractSignedTransaction(
      long keypair, String groupID, String chainID, String code, String abi, long blockLimit)
      throws JniException;

  /**
   * @param keypair
   * @param groupID
   * @param chainID
   * @param toAddr
   * @param data
   * @param blockLimit
   * @param attribute
   * @return
   * @throws JniException
   */
  public static native TxPair createSignedTransaction(
      long keypair,
      String groupID,
      String chainID,
      String toAddr,
      String data,
      long blockLimit,
      int attribute)
      throws JniException;
}
