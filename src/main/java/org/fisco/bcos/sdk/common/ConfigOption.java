package org.fisco.bcos.sdk.common;

import java.util.Set;

public class ConfigOption {

    public class EndPoint {
        private String ip;
        private short port;

        public String getIp() {
            return ip;
        }

        public void setIp(String ip) {
            this.ip = ip;
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
