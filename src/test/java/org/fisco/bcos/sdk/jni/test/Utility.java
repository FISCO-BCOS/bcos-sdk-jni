package org.fisco.bcos.sdk.jni.test;

import java.util.List;
import org.fisco.bcos.sdk.jni.common.JniConfig;

public class Utility {
  public static JniConfig newJniConfig(List<String> peers) {
    JniConfig jniConfig = new JniConfig();
    jniConfig.setPeers(peers);
    jniConfig.setCertConfig(new JniConfig.CertConfig());
    jniConfig.setSmCertConfig(new JniConfig.SMCertConfig());

    return jniConfig;
  }
}
