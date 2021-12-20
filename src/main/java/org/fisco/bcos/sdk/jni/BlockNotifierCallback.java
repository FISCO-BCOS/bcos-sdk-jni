package org.fisco.bcos.sdk.jni;

import java.math.BigInteger;

public interface BlockNotifierCallback {
  /**
   * receive block notifier
   *
   * @param groupId
   * @param blockNumber
   * @return void
   */
  void onResponse(String groupId, BigInteger blockNumber);
}
