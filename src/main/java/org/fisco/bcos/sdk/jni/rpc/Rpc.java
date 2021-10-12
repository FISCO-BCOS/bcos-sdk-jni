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

import org.fisco.bcos.sdk.jni.common.ConfigOption;

public class Rpc {

  public static native Rpc build(String group, ConfigOption config);

  public native void start();

  public native void stop();

  public native void call(String group, String to, String data, RpcCallback callback);

  public native void sendTransaction(
      String group, String data, boolean requireProof, RpcCallback callback);

  public native void getTransaction(
      String group, String txHash, boolean requireProof, RpcCallback callback);

  public native void getTransactionReceipt(
      String group, String txHash, boolean requireProof, RpcCallback callback);

  public native void getBlockByHash(
      String group, String blockHash, boolean onlyHeader, boolean onlyTxHash, RpcCallback callback);

  public native void getBlockByNumber(
      String group, long blockNumber, boolean onlyHeader, boolean onlyTxHash, RpcCallback callback);

  public native void getBlockHashByNumber(String group, long blockNumber, RpcCallback callback);

  public native void getBlockNumber(String group, RpcCallback callback);

  public native void getCode(String group, String contractAddress, RpcCallback callback);

  public native void getSealerList(String group, RpcCallback callback);

  public native void getObserverList(String group, RpcCallback callback);

  public native void getPbftView(String group, RpcCallback callback);

  public native void getPendingTxSize(String group, RpcCallback callback);

  public native void getSyncStatus(String group, RpcCallback callback);

  public native void getSystemConfigByKey(String group, String keyValue, RpcCallback callback);

  public native void getTotalTransactionCount(String group, RpcCallback callback);

  public native void getPeers(String group, RpcCallback callback);

  public native void getNodeInfo(String group, RpcCallback callback);
}
