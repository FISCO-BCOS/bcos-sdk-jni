package org.fisco.bcos.sdk.jni.test.rpc;

import java.util.Arrays;
import org.fisco.bcos.sdk.jni.common.JniConfig;
import org.fisco.bcos.sdk.jni.common.Response;
import org.fisco.bcos.sdk.jni.rpc.Rpc;
import org.fisco.bcos.sdk.jni.rpc.RpcCallback;
import org.fisco.bcos.sdk.jni.test.Utility;

public class GetBlock {

  public static void usage() {
    System.out.println("\tUsage: ");
    System.out.println(
        "\t\t\"java -cp \"conf/:lib/*:apps/*\"  org.fisco.bcos.sdk.jni.test.amop.GetBlock ip:port group");
    System.out.println("\tExample:");
    System.out.println(
        "\t\t\"java -cp \"conf/:lib/*:apps/*\"  org.fisco.bcos.sdk.jni.test.amop.GetBlock group0 127.0.0.1:20201");
    System.exit(0);
  }

  public static void main(String[] args) {
    if (args.length < 3) {
      usage();
    }

    String endpoint = args[1];
    String group = args[2];
    JniConfig jniConfig = Utility.newJniConfig(Arrays.asList(endpoint));
    Rpc rpc = Rpc.build(group, jniConfig);
    rpc.start();

    while (true) {
      rpc.getBlockNumber(
          group,
          new RpcCallback() {
            @Override
            public void onResponse(Response response) {
              System.out.println("getBlockNumber ==>>>" + response);
            }
          });

      rpc.getBlockByNumber(
          group,
          0,
          false,
          false,
          new RpcCallback() {
            @Override
            public void onResponse(Response response) {
              System.out.println("getBlockByNumber ==>>>" + response);
            }
          });
      try {
        Thread.sleep(1000);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }
}
