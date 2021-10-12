package org.fisco.bcos.sdk.jni.common;

import java.util.Set;

public class ConfigOption {

  public class EndPoint {
    private String host;
    private short port;

    public String getHost() {
      return host;
    }

    public void setHost(String host) {
      this.host = host;
    }

    public short getPort() {
      return port;
    }

    public void setPort(short port) {
      this.port = port;
    }
  }

  private Set<EndPoint> peers;

  public Set<EndPoint> getPeers() {
    return peers;
  }

  public void setPeers(Set<EndPoint> peers) {
    this.peers = peers;
  }
}
