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

package org.fisco.bcos.sdk.jni.amop;

import java.util.HashSet;
import java.util.Set;
import org.fisco.bcos.sdk.jni.common.ConfigOption;
import org.fisco.bcos.sdk.jni.common.JniLibLoader;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Amop {
  private static final Logger logger = LoggerFactory.getLogger(Amop.class);

  static {
    JniLibLoader.loadJniLibrary();
  }

  /**
   * call native c api to create amop object
   *
   * @param config
   * @return
   */
  public static native long newNativeObj(ConfigOption config);

  /**
   * @param configOption
   * @return
   */
  public static Amop build(ConfigOption configOption) {
    long nativeObj = newNativeObj(configOption);
    logger.info(" nativeObj: {}", nativeObj);
    Amop amop = new Amop();
    amop.setNativeObj(nativeObj);
    return amop;
  }

  private Amop() {}

  private long nativeObj;
  private ConfigOption configOption;

  public long getNativeObj() {
    return nativeObj;
  }

  private void setNativeObj(long nativeObj) {
    this.nativeObj = nativeObj;
  }

  public ConfigOption getConfigOption() {
    return configOption;
  }

  private void setConfigOption(ConfigOption configOption) {
    this.configOption = configOption;
  }

  // ----------------------------- Amop interface begin --------------------------------------

  public native void start();

  public native void stop();

  public native void subscribeTopic(Set<String> topicsName);

  public native void subscribeTopic(String topicName, AmopCallback callback);

  public void unsubscribeTopic(String topicName) {
    Set<String> topicsName = new HashSet<>();
    topicsName.add(topicName);
    unsubscribeTopic(topicsName);
  }

  public native void unsubscribeTopic(Set<String> topicsName);

  public native void setCallback(AmopCallback cb);

  public native AmopCallback getCallback(AmopCallback cb);

  public native void sendAmopMsg(byte[] content, AmopResponseCallback callback);

  public native void broadcastAmopMsg(byte[] content);

  public native Set<String> getSubTopics();

  // ----------------------------- Amop interface end --------------------------------------
}
