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

import org.fisco.bcos.sdk.jni.amop.Amop;
import org.fisco.bcos.sdk.jni.common.JniConfig;
import org.fisco.bcos.sdk.jni.common.JniLibLoader;
import org.fisco.bcos.sdk.jni.event.EventSubscribe;
import org.fisco.bcos.sdk.jni.rpc.Rpc;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class BcosSDK {

  private static final Logger logger = LoggerFactory.getLogger(BcosSDK.class);

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
   * @param jniConfig
   * @return
   */
  public static native BcosSDK build(JniConfig jniConfig);

  private long nativeObj;
  private JniConfig jniConfig;

  public long getNativeObj() {
    return nativeObj;
  }

  private void setNativeObj(long nativeObj) {
    this.nativeObj = nativeObj;
  }

  public JniConfig getJniConfig() {
    return jniConfig;
  }

  private void setJniConfig(JniConfig jniConfig) {
    this.jniConfig = jniConfig;
  }

  public native Rpc getRpc(String group);

  public native Amop getAmop();

  public native EventSubscribe getEventSubscribe(String group);

  public native void stopAll();
}
