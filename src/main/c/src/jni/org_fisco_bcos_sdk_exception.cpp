#include "jni/org_fisco_bcos_sdk_exception.h"
#include <string>

jint throwNoClassDefError(JNIEnv* env, const char* message)
{
    const char* className = "java/lang/NoClassDefFoundError";

    jclass exClass = env->FindClass(className);
    return env->ThrowNew(exClass, message);
}

jint throwNoSuchFieldError(JNIEnv* env, const char* message)
{
    const char* className = "java/lang/NoSuchFieldError";

    jclass exClass = env->FindClass(className);
    if (exClass == NULL)
    {
        return throwNoClassDefError(env, className);
    }

    return env->ThrowNew(exClass, message);
}

jint throwNoSuchMethodError(
    JNIEnv* env, const char* className, const char* methodName, const char* signature)
{
    const char* exClassName = "java/lang/NoSuchMethodError";

    jclass exClass = env->FindClass(exClassName);
    if (exClass == NULL)
    {
        return throwNoClassDefError(env, exClassName);
    }

    std::string exMessage;
    exMessage += className;
    exMessage += ".";
    exMessage += methodName;
    exMessage += ".";
    exMessage += signature;

    return env->ThrowNew(exClass, exMessage.c_str());
}

jint throwJniException(JNIEnv* env, const char* message)
{
    const char* className = "org/fisco/bcos/sdk/jni/common/JniException";

    jclass exClass = env->FindClass(className);
    if (exClass == NULL)
    {
        return throwNoClassDefError(env, className);
    }

    return env->ThrowNew(exClass, message);
}