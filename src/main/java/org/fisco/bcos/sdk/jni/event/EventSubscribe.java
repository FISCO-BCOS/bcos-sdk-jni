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
import org.fisco.bcos.sdk.jni.amop.Amop;
import org.fisco.bcos.sdk.jni.common.ConfigOption;
import org.fisco.bcos.sdk.jni.common.JniLibLoader;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class EventSubscribe {

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
   * @param group
   * @param configOption
   * @return
   */
  public static EventSubscribe build(String group, ConfigOption configOption) {
    long nativeObj = newNativeObj(configOption);
    logger.info(" group: {}, nativeObj: {}", group, nativeObj);
    EventSubscribe subscribe = new EventSubscribe();
    subscribe.setNativeObj(nativeObj);
    subscribe.setGroup(group);
    return subscribe;
  }

  private EventSubscribe() {}

  private long nativeObj;
  private String group;
  private ConfigOption configOption;

  public String getGroup() {
    return group;
  }

  public void setGroup(String group) {
    this.group = group;
  }

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

  // ----------------------------- EventSub interface begin --------------------------------------

  public native void start();

  public native void stop();

  public native void subscribeEvent(String params, EventSubscribeCallback callback);

  public native void unsubscribeEvent(String eventSubID, EventSubscribeCallback callback);

  public native Set<String> getAllSubscribedEvents();

  // ----------------------------- EventSub interface begin --------------------------------------
}
