package org.fisco.bcos.sdk.jni.rpc;

import org.fisco.bcos.sdk.jni.common.Error;

public abstract class RpcCallback {
  public abstract byte[] onResponse(Error error, byte[] msg);
}
