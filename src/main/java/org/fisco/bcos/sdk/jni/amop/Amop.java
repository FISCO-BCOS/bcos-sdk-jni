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
import org.fisco.bcos.sdk.jni.common.JniConfig;
import org.fisco.bcos.sdk.jni.common.JniException;
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
  public static native long newNativeObj(JniConfig config) throws JniException;

  /**
   * @param jniConfig
   * @return
   */
  public static Amop build(JniConfig jniConfig) throws JniException {
    long nativeObj = newNativeObj(jniConfig);
    Amop amop = new Amop();
    amop.setNativeObj(nativeObj);
    amop.setJniConfig(jniConfig);

    logger.info(" nativeObj: {}, jniConfig: {}", nativeObj, jniConfig);
    return amop;
  }

  private Amop() {}

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

  // ----------------------------- Amop interface begin --------------------------------------

  public native void start();

  public native void stop();

  public native void subscribeTopic(Set<String> topicsName);

  public native void subscribeTopic(String topicName, AmopRequestCallback callback);

  public void unsubscribeTopic(String topicName) {
    Set<String> topicsName = new HashSet<>();
    topicsName.add(topicName);
    unsubscribeTopic(topicsName);
  }

  public native void unsubscribeTopic(Set<String> topicsName);

  public native void setCallback(AmopRequestCallback cb);

  public native void sendAmopMsg(
      String topic, byte[] data, int timeout, AmopResponseCallback callback);

  public native void broadcastAmopMsg(String topic, byte[] data);

  public native void sendResponse(String endPoint, String seq, byte[] data);

  public native Set<String> getSubTopics();

  // ----------------------------- Amop interface end --------------------------------------
}
