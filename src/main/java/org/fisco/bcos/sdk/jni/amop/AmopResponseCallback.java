package org.fisco.bcos.sdk.jni.amop;

import org.fisco.bcos.sdk.jni.common.Error;

public abstract class AmopResponseCallback {
  public abstract void onResponse(Error error, byte[] responseData);
}
