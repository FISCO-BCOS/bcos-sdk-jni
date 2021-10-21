package org.fisco.bcos.sdk.jni.test.amop;

import java.util.Arrays;
import org.fisco.bcos.sdk.jni.amop.Amop;
import org.fisco.bcos.sdk.jni.amop.AmopResponseCallback;
import org.fisco.bcos.sdk.jni.common.JniConfig;
import org.fisco.bcos.sdk.jni.common.Response;
import org.fisco.bcos.sdk.jni.test.Utility;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class Pub {
  private static final Logger logger = LoggerFactory.getLogger(Sub.class);

  public static void usage() {
    System.out.println("\tUsage: ");
    System.out.println(
        "\t\t\"java -cp \"conf/:lib/*:apps/*\"  org.fisco.bcos.sdk.jni.test.amop.Pub ip:port topic msg");
    System.out.println("\tExample:");
    System.out.println(
        "\t\t\"java -cp \"conf/:lib/*:apps/*\"  org.fisco.bcos.sdk.jni.test.amop.Pub 127.0.0.1:20201 topic HelloWorld");
    System.exit(0);
  }

  public static void main(String[] args) {

    if (args.length < 4) {
      usage();
    }

    String peer = args[1];
    String topic = args[2];
    String msg = args[3];

    JniConfig jniConfig = Utility.newJniConfig(Arrays.asList(peer));
    Amop amop = Amop.build(jniConfig);
    amop.start();

    amop.sendAmopMsg(
        topic,
        msg.getBytes(),
        0,
        new AmopResponseCallback() {
          @Override
          public void onResponse(Response response) {
            logger.info(
                " ==> receive response message from server, errorCode: {}, errorMessage: {}, data: {}",
                response.getErrorCode(),
                response.getErrorMessage(),
                new String(response.getData()));
          }
        });
  }
}
