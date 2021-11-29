package org.fisco.bcos.sdk.jni.test.eventsub;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import java.util.Arrays;
import org.fisco.bcos.sdk.jni.common.JniConfig;
import org.fisco.bcos.sdk.jni.common.JniException;
import org.fisco.bcos.sdk.jni.common.Response;
import org.fisco.bcos.sdk.jni.event.EventSubscribe;
import org.fisco.bcos.sdk.jni.event.EventSubscribeCallback;
import org.fisco.bcos.sdk.jni.event.EventSubscribleParams;
import org.fisco.bcos.sdk.jni.test.Utility;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class EventSub {

  private static final Logger logger = LoggerFactory.getLogger(EventSub.class);

  public static void usage() {
    System.out.println("\tUsage: ");
    System.out.println(
        "\t\tjava -cp \"conf/:lib/*:apps/*\"  org.fisco.bcos.sdk.jni.test.eventsub.EventSub ip:port group fromBlk toBlk");
    System.out.println("\tExample:");
    System.out.println(
        "\t\tjava -cp \"conf/:lib/*:apps/*\"  org.fisco.bcos.sdk.jni.test.eventsub.EventSub 127.0.0.1:20201 group -1 -1");
    System.exit(0);
  }

  public static void main(String[] args)
      throws InterruptedException, JniException, JsonProcessingException {
    if (args.length < 4) {
      usage();
    }

    String peer = args[0];
    String group = args[1];
    long fromBlk = Long.valueOf(args[2]);
    long toBlk = Long.valueOf(args[3]);

    System.out.println("EventSub sample: ");
    System.out.println("\t group: " + group);
    System.out.println("\t fromBlk: " + fromBlk);
    System.out.println("\t toBlk: " + toBlk);

    JniConfig jniConfig = Utility.newJniConfig(Arrays.asList(peer));
    jniConfig.setDisableSsl(true);
    EventSubscribe eventSubscribe = EventSubscribe.build(jniConfig);

    EventSubscribleParams params = new EventSubscribleParams();
    params.setFromBlock(fromBlk);
    params.setToBlock(toBlk);

    ObjectMapper objectMapper = new ObjectMapper();
    String strParams = objectMapper.writeValueAsString(params);

    System.out.println("\t params: " + strParams);

    eventSubscribe.start();
    eventSubscribe.subscribeEvent(
        group,
        objectMapper.writeValueAsString(params),
        new EventSubscribeCallback() {
          @Override
          public void onReceiveLog(Response response) {
            System.out.println("subscribeEvent ==>>> " + response.getErrorCode());
            System.out.println("\t errorCode: " + response.getErrorCode());
            System.out.println("\t errorMessage: " + response.getErrorMessage());
            System.out.println("\t data: " + response.getData());
          }
        });

    while (true) {
      Thread.sleep(10000);
    }
  }
}
