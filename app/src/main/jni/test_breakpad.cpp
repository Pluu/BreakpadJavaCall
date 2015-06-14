#include <jni.h>
#include <android/log.h>
#include <stdio.h>

#include "google_breakpad/src/client/linux/handler/exception_handler.h"
#include "google_breakpad/src/client/linux/handler/minidump_descriptor.h"

static google_breakpad::ExceptionHandler* exceptionHandler;
bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context,
                  bool succeeded) {

    __android_log_print(ANDROID_LOG_DEBUG, "PluuSystem", "Dump path: %s\n", descriptor.path());
    return succeeded;
}

void Crash() {
    volatile int* a = reinterpret_cast<volatile int*>(NULL);
    *a = 1;
}

extern "C" {
    void Java_com_pluusystem_breakpadjavacall_MainActivity_initNative(JNIEnv* env, jobject obj, jstring filepath)
    {
        const char *path = env->GetStringUTFChars(filepath, 0);
        google_breakpad::MinidumpDescriptor descriptor(path);
        exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, DumpCallback, NULL, true, -1);

        __android_log_print(ANDROID_LOG_DEBUG, "PluuSystem", "initNative cal");
    }

    void Java_com_pluusystem_breakpadjavacall_MainActivity_crashService(JNIEnv* env, jobject obj)
    {
    	__android_log_print(ANDROID_LOG_DEBUG, "PluuSystem", "crashService call");

        Crash();
    }

}
