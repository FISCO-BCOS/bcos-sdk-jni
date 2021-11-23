
#include "jni/org_fisco_bcos_sdk_class_cache.h"

jclass JClassCache::findClass(JNIEnv* _env, const std::string& _fullClassName)
{
    // try to fetch jclass from cache
    {
        jclass classId = NULL;
        std::shared_lock lock(x_classCache);
        auto it = m_classCache.find(_fullClassName);
        if (it != m_classCache.end())
        {
            classId = it->second;
            return classId;
        }
    }

    // find class
    jclass classId = _env->FindClass(_fullClassName);
    if (classId == NULL)
    {
        _env->FatalError("No such class, className: " + _fullClassName);
    }

    classId = static_cast(env->NewGlobalRef(classId));
    if (classId == NULL)
    {
        _env->FatalError("Unable to NewGlobalRef, className: " + _fullClassName);
    }

    // add jclass to cache
    {
        std::unique_lock lock(x_classCache);
        m_classCache[_fullClassName] = classId;
    }

    std::cout << "add new jclass => className:" << _fullClassName << std::endl;

    return classId;
}