package org.fisco.bcos.sdk.jni.common;

import java.util.List;

public class JniConfig {

  private int threadPoolSize = 4;
  private int reconnectPeriodMs = 10000;
  private int heartbeatPeriodMs = 10000;
  private int messageTimeoutMs = 10000;

  private List<String> peers;

  public List<String> getPeers() {
    return peers;
  }

  public void setPeers(List<String> peers) {
    this.peers = peers;
  }

  public int getThreadPoolSize() {
    return threadPoolSize;
  }

  public void setThreadPoolSize(int threadPoolSize) {
    this.threadPoolSize = threadPoolSize;
  }

  public int getReconnectPeriodMs() {
    return reconnectPeriodMs;
  }

  public void setReconnectPeriodMs(int reconnectPeriodMs) {
    this.reconnectPeriodMs = reconnectPeriodMs;
  }

  public int getHeartbeatPeriodMs() {
    return heartbeatPeriodMs;
  }

  public void setHeartbeatPeriodMs(int heartbeatPeriodMs) {
    this.heartbeatPeriodMs = heartbeatPeriodMs;
  }

  public int getMessageTimeoutMs() {
    return messageTimeoutMs;
  }

  public void setMessageTimeoutMs(int messageTimeoutMs) {
    this.messageTimeoutMs = messageTimeoutMs;
  }

  @Override
  public String toString() {
    return "ConfigOption{" + "peers=" + peers + '}';
  }
}
