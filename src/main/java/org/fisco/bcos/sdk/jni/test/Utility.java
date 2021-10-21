package org.fisco.bcos.sdk.jni.test;

import java.util.List;
import org.fisco.bcos.sdk.jni.common.JniConfig;

public class Utility {
  public static JniConfig newJniConfig(List<String> peers) {
    JniConfig jniConfig = new JniConfig();
    jniConfig.setPeers(peers);
    return jniConfig;
  }
}
