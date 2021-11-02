
#include <jni.h>
/* Header for class common */

#ifndef _Included_org_fisco_bcos_sdk_jni_exception
#define _Included_org_fisco_bcos_sdk_jni_exception
#ifdef __cplusplus
extern "C" {
#endif

#define IF_THROW_NO_SUCH_FIELD_EXCEPTION(env, field, msg) \
    do                                                    \
    {                                                     \
        if (field == NULL)                                \
        {                                                 \
            throwNoSuchFieldError(env, msg);              \
        }                                                 \
    } while (0)

#define IF_THROW_NO_SUCH_METHOD_EXCEPTION(env, class, method, sig) \
    do                                                             \
    {                                                              \
        if (obj == NULL)                                           \
        {                                                          \
            throwNoSuchMethodError(env, class, method, sig);       \
        }                                                          \
    } while (0)

#define IF_THROW_NO_CLASS_EXCEPTION(env, msg) \
    do                                        \
    {                                         \
        if (obj == NULL)                      \
        {                                     \
            throwNoClassDefError(env, msg);   \
        }                                     \
    } while (0)

jint throwNoSuchFieldError(JNIEnv* env, const char* message);
jint throwNoSuchMethodError(
    JNIEnv* env, const char* className, const char* methodName, const char* signature);
jint throwNoClassDefError(JNIEnv* env, const char* message);
jint throwJniException(JNIEnv* env, const char* message);

#ifdef __cplusplus
}
#endif
#endif
