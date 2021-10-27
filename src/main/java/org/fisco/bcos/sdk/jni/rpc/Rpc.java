/*
 * Copyright 2014-2020  [fisco-dev]
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 *
 */

package org.fisco.bcos.sdk.jni.rpc;

import org.fisco.bcos.sdk.jni.common.JniConfig;
import org.fisco.bcos.sdk.jni.common.JniLibLoader;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Rpc {
  private static final Logger logger = LoggerFactory.getLogger(Rpc.class);

  static {
    JniLibLoader.loadJniLibrary();
  }

  /**
   * call native c api to create rpc object
   *
   * @param config
   * @return
   */
  public static native long newNativeObj(JniConfig config);

  /**
   * @param group
   * @param jniConfig
   * @return
   */
  public static Rpc build(String group, JniConfig jniConfig) {
    long nativeObj = newNativeObj(jniConfig);
    if (nativeObj == 0L) {
      // TODO: create native obj failed and how to print error code、error messages and handle to
      // error handing
    }

    logger.info(" group: {}, nativeObj: {}", group, nativeObj);
    Rpc rpc = new Rpc();
    rpc.setGroup(group);
    rpc.setNativeObj(nativeObj);
    return rpc;
  }

  private Rpc() {}

  private long nativeObj;
  private JniConfig jniConfig;
  private String group;

  public JniConfig getJniConfig() {
    return jniConfig;
  }

  private void setJniConfig(JniConfig jniConfig) {
    this.jniConfig = jniConfig;
  }

  public String getGroup() {
    return group;
  }

  public void setGroup(String group) {
    this.group = group;
  }

  public long getNativeObj() {
    return nativeObj;
  }

  private void setNativeObj(long nativeObj) {
    this.nativeObj = nativeObj;
  }

  // ----------------------------- RPC interface begin --------------------------------------

  public native void start();

  public native void stop();

  public native void genericMethod(String data, RpcCallback callback);

  public native void genericMethod(String group, String data, RpcCallback callback);

  public native void genericMethod(String group, String node, String data, RpcCallback callback);

  public native void call(String to, String data, RpcCallback callback);

  public native void sendTransaction(String data, boolean requireProof, RpcCallback callback);

  public native void getTransaction(String txHash, boolean requireProof, RpcCallback callback);

  public native void getTransactionReceipt(
      String txHash, boolean requireProof, RpcCallback callback);

  public native void getBlockByHash(
      String blockHash, boolean onlyHeader, boolean onlyTxHash, RpcCallback callback);

  public native void getBlockByNumber(
      long blockNumber, boolean onlyHeader, boolean onlyTxHash, RpcCallback callback);

  public native void getBlockHashByNumber(long blockNumber, RpcCallback callback);

  public native void getBlockNumber(RpcCallback callback);

  public native void getCode(String contractAddress, RpcCallback callback);

  public native void getSealerList(RpcCallback callback);

  public native void getObserverList(RpcCallback callback);

  public native void getPbftView(RpcCallback callback);

  public native void getPendingTxSize(RpcCallback callback);

  public native void getSyncStatus(RpcCallback callback);

  public native void getSystemConfigByKey(String keyValue, RpcCallback callback);

  public native void getTotalTransactionCount(RpcCallback callback);

  public native void getPeers(RpcCallback callback);

  public native void getGroupList();

  public native void getGroupInfoList();

  public native void getGroupNodeInfo();

  // ----------------------------- RPC interface end --------------------------------------
}
