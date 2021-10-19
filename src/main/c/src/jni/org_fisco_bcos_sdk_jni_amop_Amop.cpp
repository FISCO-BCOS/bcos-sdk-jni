#include "jni/org_fisco_bcos_sdk_jni_amop_Amop.h"
#include "bcos_sdk_c.h"
#include "bcos_sdk_c_amop.h"
#include "bcos_sdk_c_common.h"
#include "jni/common.h"
#include <algorithm>
#include <cstdio>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    newNativeObj
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/JniConfig;)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_newNativeObj(
    JNIEnv* env, jclass, jobject jconfig)
{
    // config
    struct bcos_sdk_c_config* config = init_bcos_sdk_c_config(env, jconfig);
    // create amop obj
    void* amop = bcos_sdk_create_amop(config);
    // destroy config
    bcos_sdk_c_config_destroy(config);
    if (amop == NULL)
    {
        // TODO: how to handler the error
        env->FatalError("bcos_sdk_create_amop return NULL");
    }

    return reinterpret_cast<jlong>(amop);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_start(JNIEnv* env, jobject self)
{
    void* amop = obtain_native_object(env, self);
    bcos_sdk_start_amop(amop);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_stop(JNIEnv* env, jobject self)
{
    void* amop = obtain_native_object(env, self);
    bcos_sdk_stop_amop(amop);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    subscribeTopic
 * Signature: (Ljava/util/Set;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_subscribeTopic__Ljava_util_Set_2(
    JNIEnv* env, jobject self, jobject jtopics)
{
    void* amop = obtain_native_object(env, self);

    jclass setClass = env->GetObjectClass(jtopics);

    /*
      Use javap to get propper descriptor
      > javap -s -p java.util.Set | grep -A 1 toArray
      public abstract java.lang.Object[] toArray();
      descriptor: ()[Ljava/lang/Object;
    */
    jmethodID toArrayMethodID = env->GetMethodID(setClass, "toArray", "()[Ljava/lang/Object;");

    // Set.toArray() => set array
    jobjectArray arrayOfElements = (jobjectArray)env->CallObjectMethod(jtopics, toArrayMethodID);

    // set array size
    int arraySize = env->GetArrayLength(arrayOfElements);
    if (arraySize > 0)
    {
        char** topics = (char**)malloc(arraySize * sizeof(char*));
        for (int i = 0; i < arraySize; i++)
        {
            jstring stringObj = (jstring)env->GetObjectArrayElement(arrayOfElements, i);
            const char* topic = env->GetStringUTFChars(stringObj, 0);
            printf(" ==> index: %d, topic: %s\n", i, topic);
            topics[i] = strdup(topic);
            env->ReleaseStringUTFChars(stringObj, topic);
        }

        bcos_amop_subscribe_topic(amop, topics, arraySize);

        for (int i = 0; i < arraySize; i++)
        {
            free(topics[i]);
        }
    }
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    subscribeTopic
 * Signature: (Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/amop/AmopCallback;)V
 */
JNIEXPORT void JNICALL
Java_org_fisco_bcos_sdk_jni_amop_Amop_subscribeTopic__Ljava_lang_String_2Lorg_fisco_bcos_sdk_jni_amop_AmopCallback_2(
    JNIEnv* env, jobject self, jstring jtopic, jobject jcallback)
{
    void* amop = obtain_native_object(env, self);
    (void)amop;

    const char* topic = env->GetStringUTFChars(jtopic, 0);

    (void)jcallback;

    // release topic
    env->ReleaseStringUTFChars(jtopic, topic);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    unsubscribeTopic
 * Signature: (Ljava/util/Set;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_unsubscribeTopic(
    JNIEnv* env, jobject self, jobject jtopics)
{
    void* amop = obtain_native_object(env, self);

    jclass setClass = env->GetObjectClass(jtopics);

    /*
      Use javap to get propper descriptor
      > javap -s -p java.util.Set | grep -A 1 toArray
      public abstract java.lang.Object[] toArray();
      descriptor: ()[Ljava/lang/Object;
    */
    jmethodID toArrayMethodID = env->GetMethodID(setClass, "toArray", "()[Ljava/lang/Object;");

    // Set.toArray() => set array
    jobjectArray arrayOfElements = (jobjectArray)env->CallObjectMethod(jtopics, toArrayMethodID);

    // set array size
    int arraySize = env->GetArrayLength(arrayOfElements);
    if (arraySize > 0)
    {
        char** topics = (char**)malloc(arraySize * sizeof(char*));
        for (int i = 0; i < arraySize; i++)
        {
            jstring stringObj = (jstring)env->GetObjectArrayElement(arrayOfElements, i);
            const char* topic = env->GetStringUTFChars(stringObj, 0);
            topics[i] = strdup(topic);
            env->ReleaseStringUTFChars(stringObj, topic);
        }

        bcos_amop_unsubscribe_topic(amop, topics, arraySize);

        for (int i = 0; i < arraySize; i++)
        {
            free(topics[i]);
        }
    }
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    setCallback
 * Signature: (Lorg/fisco/bcos/sdk/jni/amop/AmopCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_setCallback(
    JNIEnv* env, jobject, jobject callback)
{
    std::ignore = env;
    std::ignore = callback;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    sendAmopMsg
 * Signature: ([BLorg/fisco/bcos/sdk/jni/amop/AmopResponseCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_sendAmopMsg(
    JNIEnv* env, jobject, jbyteArray data, jobject callback)
{
    std::ignore = env;
    std::ignore = data;
    std::ignore = callback;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    broadcastAmopMsg
 * Signature: (Ljava/lang/String;[B)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_broadcastAmopMsg(
    JNIEnv* env, jobject self, jstring jtopic, jbyteArray jdata)
{
    void* amop = obtain_native_object(env, self);

    const char* topic = env->GetStringUTFChars(jtopic, 0);
    jsize len = env->GetArrayLength(jdata);
    jbyte* data = (jbyte*)env->GetByteArrayElements(jdata, 0);

    std::string msg;
    msg.insert(msg.begin(), (char*)data, (char*)data + len);
    // printf(" ===>>>> broadcast message: %s\n", msg.c_str());

    bcos_amop_broadcast(amop, topic, (void*)data, (size_t)len);

    // release topic
    env->ReleaseStringUTFChars(jtopic, topic);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_amop_Amop
 * Method:    getSubTopics
 * Signature: ()Ljava/util/Set;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_amop_Amop_getSubTopics(
    JNIEnv* env, jobject self)
{
    std::ignore = env;
    std::ignore = self;

    return jobject();
}
