
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
    JNIEnv* env;
    jobject jcallback;
};


struct bcos_sdk_c_config* init_bcos_sdk_c_config(JNIEnv* env, jobject jconfig);

#ifdef __cplusplus
}
#endif
#endif
