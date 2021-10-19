package org.fisco.bcos.sdk.jni.sample;

import java.util.ArrayList;
import java.util.List;
import org.fisco.bcos.sdk.jni.common.JniConfig;
import org.fisco.bcos.sdk.jni.rpc.Rpc;

public class RpcTest {
  public static void main(String[] args) {
    JniConfig jniConfig = new JniConfig();
    List<String> peers = new ArrayList<>();
    peers.add("127.0.0.1:20201");
    peers.add("127.0.0.1:20202");
    peers.add("127.0.0.1:20203");
    peers.add("127.0.0.1:20204");
    peers.add("127.0.0.1:20205");
    jniConfig.setPeers(peers);
    Rpc rpc = Rpc.build("group", jniConfig);
    rpc.start();

    while (true) {
      rpc.getBlockByNumber(1, true, false, null);
      try {
        Thread.sleep(1000);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }

    }

  }
}
