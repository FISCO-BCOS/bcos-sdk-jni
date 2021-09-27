package org.fisco.bcos.sdk.amop;

public abstract class AmopResponseCallback {
  public abstract void onResponse(Error error, byte[] responseData);
}
