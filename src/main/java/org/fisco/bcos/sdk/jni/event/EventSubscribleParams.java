package org.fisco.bcos.sdk.jni.event;

import java.util.List;

public class EventSubscribleParams {
    private long fromBlock;
    private long toBlock;
    private List<String> address;
    private List<List<String>> topics;

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

    public List<String> getAddress() {
        return address;
    }

    public void setAddress(List<String> address) {
        this.address = address;
    }

    public List<List<String>> getTopics() {
        return topics;
    }

    public void setTopics(List<List<String>> topics) {
        this.topics = topics;
    }
}
