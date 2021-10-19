package org.fisco.bcos.sdk.jni.rpc;

import org.fisco.bcos.sdk.jni.common.Error;

public interface RpcCallback {
  void onResponse(Error error, byte[] msg);
}
