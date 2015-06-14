#include <jni.h>
#include <android/log.h>
#include <stdio.h>

#include "google_breakpad/src/client/linux/handler/exception_handler.h"
#include "google_breakpad/src/client/linux/handler/minidump_descriptor.h"

JNIEnv * jEnv = 0;
static google_breakpad::ExceptionHandler* exceptionHandler;

bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor,
                  void* context,
                  bool succeeded) {

    __android_log_print(ANDROID_LOG_DEBUG, "PluuSystem", "Dump path: %s\n", descriptor.path());

    jclass cls = jEnv->FindClass("com/pluusystem/breakpadjavacall/NativeController");

    if(cls == NULL) {
      return false;
    }

    jmethodID mhthod = jEnv->GetStaticMethodID(cls, "NativeCrashCallback", "(Ljava/lang/String;)I");
    if(mhthod == NULL) {
      return false;
    }

    const char* path = descriptor.path();

    jstring jstr = jEnv->NewStringUTF(path);
    if (jstr == NULL) {
      return false;
    }

    jint i = jEnv->CallStaticIntMethod(cls, mhthod, jstr);

    return succeeded;
}

void Crash() {
    volatile int* a = reinterpret_cast<volatile int*>(NULL);
    *a = 1;
}

extern "C" {
    void Java_com_pluusystem_breakpadjavacall_MainActivity_initNative(JNIEnv* env, jobject obj, jstring filepath)
    {
        jEnv = env;

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
