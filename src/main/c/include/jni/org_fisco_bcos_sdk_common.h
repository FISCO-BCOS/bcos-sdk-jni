
#include "bcos_sdk_c_common.h"
#include <jni.h>
/* Header for class common */

#ifndef _Included_org_fisco_bcos_sdk_jni_common
#define _Included_org_fisco_bcos_sdk_jni_common
#ifdef __cplusplus
extern "C" {
#endif

struct cb_context
{
    JavaVM* jvm;
    jobject jcallback;
};

void* get_obj_native_member(JNIEnv* env, jobject self);

struct bcos_sdk_c_config* create_bcos_sdk_c_config_from_java_obj(JNIEnv* env, jobject jconfig);

#ifdef __cplusplus
}
#endif
#endif
