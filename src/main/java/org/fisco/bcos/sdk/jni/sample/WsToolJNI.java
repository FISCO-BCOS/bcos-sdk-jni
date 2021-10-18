package org.fisco.bcos.sdk.jni.sample;

import org.fisco.bcos.sdk.jni.common.JniLibLoader;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class WsToolJNI {
  private static final Logger logger = LoggerFactory.getLogger(WsToolJNI.class);

  static {
    JniLibLoader.loadJniLibrary();
  }

  public WsToolJNI() {
    this.nativeObjPointer = newWsToolJNI();
    logger.info("nativeObjPointer = " + nativeObjPointer);
  }

  private long nativeObjPointer;

  public long getNativeObjectPointer() {
    return nativeObjPointer;
  }

  public void setNativeObjectPointer(long nativeObjectPointer) {
    this.nativeObjPointer = nativeObjectPointer;
  }

  public native long newWsToolJNI();

  public native boolean validIP(String ip);

  public native boolean validPort(short port);

  public static void main(String[] args) {
    if (args.length < 2) {
      System.out.println("Please provider ip and port, eg: 127.0.0.1 12345.");
      System.exit(0);
    }
    WsToolJNI configJNI = new WsToolJNI();
    boolean validIP = configJNI.validIP(args[0]);
    boolean validPort = configJNI.validPort(Short.valueOf(args[1]));

    System.out.println(" validIP: " + validIP);
    System.out.println(" validPort: " + validPort);
  }
}
