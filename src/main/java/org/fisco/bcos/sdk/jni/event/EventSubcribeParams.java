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

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class EventSubcribeParams {
  // TODO:
  public static final int MAX_EVENT_LOG_COUNT = 4;

  private long fromBlock;
  private long toBlock;
  private List<String> addresses = new ArrayList<>();
  private List<Set<String>> topics = new ArrayList<>();

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

  public List<Set<String>> getTopics() {
    return topics;
  }

  public void setTopics(List<Set<String>> topics) {
    this.topics = topics;
  }

  public boolean addAddress(String address) {
    return addresses.add(address);
  }

  public boolean addTopic(int index, String topic) {
    Set<String> topicSet = topics.get(index);
    if (topicSet == null) {
      topicSet = new HashSet<String>();
      topicSet.add(topic);
      topics.set(index, topicSet);
    } else {
      topicSet.add(topic);
    }

    return true;
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
