#include "org_fisco_bcos_sdk_jni_sample_WsToolJNI.h"
#include <bcos-boostssl/websocket/WsTools.h>
#include <cstdio>

static bcos::boostssl::ws::WsTools *getWsToolsObj(JNIEnv *env, jobject self) {
  jclass cls = env->GetObjectClass(self);
  if (!cls) {
    env->FatalError("GetObjectClass failed");
  }

  jfieldID nativeObjPointerID = env->GetFieldID(cls, "nativeObjPointer", "J");
  if (!nativeObjPointerID) {
    env->FatalError("GetFieldID failed");
  }

  jlong nativeObjPointer = env->GetLongField(self, nativeObjPointerID);
  return reinterpret_cast<bcos::boostssl::ws::WsTools *>(nativeObjPointer);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_sample_WsToolJNI
 * Method:    newWsToolJNI
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL
Java_org_fisco_bcos_sdk_jni_sample_WsToolJNI_newWsToolJNI(JNIEnv *, jobject) {
  auto tools = new bcos::boostssl::ws::WsTools();
  return reinterpret_cast<jlong>(tools);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_sample_WsToolJNI
 * Method:    validIP
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_fisco_bcos_sdk_jni_sample_WsToolJNI_validIP(
    JNIEnv *_env, jobject _self, jstring _ip) {
  auto *tools = getWsToolsObj(_env, _self);

  const char *raw = _env->GetStringUTFChars(_ip, NULL);
  std::string ip(raw);
  _env->ReleaseStringUTFChars(_ip, raw);

  printf(" => ip = %s", ip.c_str());

  return static_cast<jboolean>(tools->validIP(ip));
}

/*
 * Class:     org_fisco_bcos_sdk_jni_sample_WsToolJNI
 * Method:    validPort
 * Signature: (S)Z
 */
JNIEXPORT jboolean JNICALL
Java_org_fisco_bcos_sdk_jni_sample_WsToolJNI_validPort(JNIEnv *_env,
                                                       jobject _self,
                                                       jshort _port) {
  auto *tools = getWsToolsObj(_env, _self);

  printf(" => port = %d", _port);

  return static_cast<jboolean>(tools->validPort(_port));
}