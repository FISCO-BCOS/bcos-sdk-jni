#include "jni/org_fisco_bcos_sdk_exception.h"
#include <iostream>
#include <string>

void ThrowJNIException(JNIEnv* env, const char* kpFile, int iLine, const std::string& message)
{
    const char* className = "org/fisco/bcos/sdk/jni/common/JniException";
    std::string errorMessage;
    (void)kpFile;
    (void)iLine;
    /*
    errorMessage  = "JNIException!";
    if (kpFile != NULL && !message.empty())
    {
        errorMessage += "\nFile: " + std::string(kpFile) +
                        "\nLine number: " + std::to_string(iLine) + +"\nReason: \n" + message;
    }
    */
    errorMessage = message;

    // Find the exception class.
    jclass tClass = env->FindClass(className);
    if (env->ExceptionCheck())
    {
        env->ExceptionDescribe();
        env->ExceptionClear();  // Make sure to clear it
        std::cerr << " Not found exception class: " << className << std::endl;
        tClass = env->FindClass("java/lang/Exception");
        if (tClass == NULL)
        {
            std::cerr << " Not found exception class: "
                      << "java/lang/Exception" << std::endl;
            env->DeleteLocalRef(tClass);
            return;
        }
    }

// Notice: debug info
#if 0
    std::cerr << "jni exception throw"
              << " ,msg: " << message << std::endl;
#endif

    // Throw the exception with error info
    env->ThrowNew(tClass, errorMessage.c_str());
    env->DeleteLocalRef(tClass);
}
