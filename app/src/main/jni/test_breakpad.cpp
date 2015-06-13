#include <jni.h>
#include <stdio.h>
#include <android/log.h>

extern "C" {
    void Java_com_pluusystem_breakpadjavacall_MainActivity_initNative(JNIEnv* env, jobject obj, jstring filepath)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "PluuSystem", "initNative cal");
    }

    void Java_com_pluusystem_breakpadjavacall_MainActivity_crashService(JNIEnv* env, jobject obj)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "PluuSystem", "crashService call");
    }

}
