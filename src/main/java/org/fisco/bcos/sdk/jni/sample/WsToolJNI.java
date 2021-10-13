package org.fisco.bcos.sdk.jni.sample;

public class WsToolJNI {

  static {
    System.loadLibrary("fisco-bcos-jni");
  }

  public WsToolJNI() {
    this.nativeObjPointer = newWsToolJNI();
    System.out.println("nativeObjPointer = " + nativeObjPointer);
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
