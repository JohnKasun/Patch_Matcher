#include <jni.h>
#include <string>
#include "AudioEngine.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_patch_1matcher_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    AudioEngine engine;
    return env->NewStringUTF(hello.c_str());
}