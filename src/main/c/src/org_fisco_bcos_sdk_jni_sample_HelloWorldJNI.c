#include "org_fisco_bcos_sdk_jni_sample_HelloWorldJNI.h"

#include <stdio.h>

JNIEXPORT void JNICALL Java_Hello_sayHi
(JNIEnv *env, jobject obj, jstring who, jint times) {
	jint i;
	jboolean iscopy;
	const char *name;
	name = (*env)->GetStringUTFChars(env, who, &iscopy);
	for (i = 0; i < times; i++) {
		printf("Hello %s\n", name);
	}
}