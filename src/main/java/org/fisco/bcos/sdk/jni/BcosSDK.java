/**
 * Copyright 2014-2020 [fisco-dev]
 *
 * <p>Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of the License at
 *
 * <p>http://www.apache.org/licenses/LICENSE-2.0
 *
 * <p>Unless required by applicable law or agreed to in writing, software distributed under the
 * License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.fisco.bcos.sdk.jni;

import org.fisco.bcos.sdk.jni.common.JniConfig;
import org.fisco.bcos.sdk.jni.common.JniException;
import org.fisco.bcos.sdk.jni.common.JniLibLoader;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class BcosSDK {

  private static final Logger logger = LoggerFactory.getLogger(BcosSDK.class);

  static {
    JniLibLoader.loadJniLibrary();
  }

  private BcosSDK() {}

  /**
   * @param jniConfig
   * @return
   */
  public static BcosSDK build(JniConfig jniConfig) throws JniException {
    long nativeObj = newNativeObj(jniConfig);
    logger.info("newNativeObj, nativeObj: {}, jniConfig: {}", nativeObj, jniConfig);
    BcosSDK sdk = new BcosSDK();
    sdk.setNativeObj(nativeObj);
    return sdk;
  }

  private long nativeObj;

  public long getNativeObj() {
    return nativeObj;
  }

  private void setNativeObj(long nativeObj) {
    this.nativeObj = nativeObj;
  }

  // ---------------------------------------------------------------------------------------
  /**
   * call native c api to create rpc object
   *
   * @param config
   * @return
   */
  public static native long newNativeObj(JniConfig config) throws JniException;

  public native long getRpcNativeObj();

  public native long getAmopNative();

  public native long getEventSubNative();

  public native void destroy();
  // -----------------------------------------------------------------------------------------
}
