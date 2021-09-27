package org.fisco.bcos.sdk.rpc;

public abstract class RpcCallback {
  public abstract byte[] onResponse(Error error, byte[] msg);
}
