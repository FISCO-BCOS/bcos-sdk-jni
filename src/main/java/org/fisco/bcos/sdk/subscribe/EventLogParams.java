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

package org.fisco.bcos.sdk.subscribe;

import java.util.List;

public class EventLogParams {
  private long fromBlock;
  private long toBlock;
  private List<String> addresses;
  private List<Object> topics;

  public long getFromBlock() {
    return fromBlock;
  }

  public void setFromBlock(long fromBlock) {
    this.fromBlock = fromBlock;
  }

  public long getToBlock() {
    return toBlock;
  }

  public void setToBlock(long toBlock) {
    this.toBlock = toBlock;
  }

  public List<String> getAddresses() {
    return addresses;
  }

  public void setAddresses(List<String> addresses) {
    this.addresses = addresses;
  }

  public List<Object> getTopics() {
    return topics;
  }

  public void setTopics(List<Object> topics) {
    this.topics = topics;
  }

  @Override
  public String toString() {
    return "EventLogFilterParams [fromBlock="
        + fromBlock
        + ", toBlock="
        + toBlock
        + ", addresses="
        + addresses
        + ", topics="
        + topics
        + "]";
  }
}
