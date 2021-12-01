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

package org.fisco.bcos.sdk.jni.event;

import java.util.Set;
import org.fisco.bcos.sdk.jni.common.JniConfig;
import org.fisco.bcos.sdk.jni.common.JniException;
import org.fisco.bcos.sdk.jni.common.JniLibLoader;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class EventSubscribe {

  private static final Logger logger = LoggerFactory.getLogger(EventSubscribe.class);

  static {
    JniLibLoader.loadJniLibrary();
  }

  /**
   * call native c api to create amop object
   *
   * @param config
   * @return
   */
  private static native long newNativeObj(JniConfig config) throws JniException;

  /**
   * @param jniConfig
   * @return
   */
  public static EventSubscribe build(JniConfig jniConfig) throws JniException {
    long nativeObj = newNativeObj(jniConfig);

    EventSubscribe subscribe = new EventSubscribe();
    subscribe.setNativeObj(nativeObj);

    logger.info(" nativeObj: {}，jniConfig: {}", nativeObj, jniConfig);
    return subscribe;
  }

  /**
   * @param nativeObj
   * @return
   * @throws JniException
   */
  public static EventSubscribe build(long nativeObj) throws JniException {
    EventSubscribe subscribe = new EventSubscribe();
    subscribe.setNativeObj(nativeObj);

    logger.info(" nativeObj: {}", nativeObj);
    return subscribe;
  }

  private EventSubscribe() {}

  private long nativeObj;

  public long getNativeObj() {
    return nativeObj;
  }

  private void setNativeObj(long nativeObj) {
    this.nativeObj = nativeObj;
  }

  // ----------------------------- EventSub interface begin --------------------------------------

  public native void start();

  public native void stop();

  public native String subscribeEvent(String group, String params, EventSubscribeCallback callback);

  public native void unsubscribeEvent(String eventID);

  public native Set<String> getAllSubscribedEvents();

  // ----------------------------- EventSub interface begin --------------------------------------
}
