package org.fisco.bcos.sdk.jni.test.amop;

import java.util.Arrays;
import org.fisco.bcos.sdk.jni.amop.Amop;
import org.fisco.bcos.sdk.jni.amop.AmopRequestCallback;
import org.fisco.bcos.sdk.jni.common.JniConfig;
import org.fisco.bcos.sdk.jni.test.Utility;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Sub {

  private static final Logger logger = LoggerFactory.getLogger(Sub.class);

  public static void usage() {
    System.out.println("\tUsage: ");
    System.out.println(
        "\t\t\"java -cp \"conf/:lib/*:apps/*\"  org.fisco.bcos.sdk.jni.test.amop.Sub ip:port topic");
    System.out.println("\tExample:");
    System.out.println(
        "\t\t\"java -cp \"conf/:lib/*:apps/*\"  org.fisco.bcos.sdk.jni.test.amop.Sub 127.0.0.1:20201 topic");
    System.exit(0);
  }

  public static void main(String[] args) {
    /*
    if (args.length < 3) {
        usage();
    }

    String peer = args[1];
    String topic = args[2];
    */
    String peer = "127.0.0.1:20203";
    String topic = "topic";

    JniConfig jniConfig = Utility.newJniConfig(Arrays.asList(peer));
    Amop amop = Amop.build(jniConfig);
    amop.start();

    amop.subscribeTopic(
        topic,
        new AmopRequestCallback() {
          @Override
          public void onRequest(String endpoint, String seq, byte[] data) {
            logger.info(
                " ==> receive message from client, endpoint: {}, seq: {}, data: {}",
                endpoint,
                seq,
                new String(data));
            amop.sendResponse(endpoint, seq, data);
          }
        });

    while (true) {
      try {
        Thread.sleep(10000);
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
  }
}
