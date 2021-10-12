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

import org.fisco.bcos.sdk.jni.common.ConfigOption;
import org.fisco.bcos.sdk.jni.rpc.Rpc;

public class BcosSDK {

  private ConfigOption config = null;

  public static BcosSDK build(String configPath) {
    return null;
  }

  public BcosSDK(ConfigOption configOption) {}

  public Rpc getClientByGroupID(String groupId) {
    return null;
  }

  public Rpc getClientByEndpoint(String endPoint) {
    return null;
  }

  public ConfigOption getConfig() {
    return config;
  }

  public void setConfig(ConfigOption config) {
    this.config = config;
  }

  public void stopAll() {}
}
