#include "jni/org_fisco_bcos_sdk_jni_event_EventSubscribe.h"
#include "bcos_sdk_c.h"
#include <tuple>

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    newNativeObj
 * Signature: (Lorg/fisco/bcos/sdk/jni/common/ConfigOption;)J
 */
JNIEXPORT jlong JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_newNativeObj(
    JNIEnv* env, jclass, jobject)
{
    struct bcos_sdk_struct_config config;
    // TODO: init config
    void* amop = bcos_sdk_create_event_sub(&config);
    if (amop == NULL)
    {
        // TODO: error handler
        env->FatalError("bcos_sdk_create_event_sub return NULL");
    }
    return reinterpret_cast<jlong>(amop);
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    start
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_start(
    JNIEnv* env, jobject self)
{
    std::ignore = env;
    std::ignore = self;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_stop(
    JNIEnv* env, jobject self)
{
    std::ignore = env;
    std::ignore = self;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    subscribeEvent
 * Signature: (Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/event/EventSubscribeCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_subscribeEvent(
    JNIEnv* env, jobject self, jstring params, jobject callback)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = params;
    std::ignore = callback;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    unsubscribeEvent
 * Signature: (Ljava/lang/String;Lorg/fisco/bcos/sdk/jni/event/EventSubscribeCallback;)V
 */
JNIEXPORT void JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_unsubscribeEvent(
    JNIEnv* env, jobject self, jstring params, jobject callback)
{
    std::ignore = env;
    std::ignore = self;
    std::ignore = params;
    std::ignore = callback;
}

/*
 * Class:     org_fisco_bcos_sdk_jni_event_EventSubscribe
 * Method:    getAllSubscribedEvents
 * Signature: ()Ljava/util/Set;
 */
JNIEXPORT jobject JNICALL Java_org_fisco_bcos_sdk_jni_event_EventSubscribe_getAllSubscribedEvents(
    JNIEnv* env, jobject self)
{
    std::ignore = env;
    std::ignore = self;
    return jobject();
}
