#include <jni.h>
#include <string>
#include "AudioEngine.h"

AudioEngine engine;

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_patch_1matcher_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_patch_1matcher_MainActivity_onPlayButtonPress(JNIEnv *env, jobject thiz) {
    engine.startAudio();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_patch_1matcher_MainActivity_onStopButtonPress(JNIEnv *env, jobject thiz) {
    engine.pauseAudio();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_patch_1matcher_MainActivity_onChangeButtonPress(JNIEnv *env, jobject thiz) {
    engine.changeWavetable();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_patch_1matcher_MainActivity_onFeedbackEnable(JNIEnv *env, jobject thiz) {
    engine.enableFeedback();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_patch_1matcher_MainActivity_onConnectButtonPress(JNIEnv *env, jobject thiz) {
    static bool connected{false};
    if (!connected)
        engine.operatorInterface[1]->connectTo(engine.operatorInterface[0]);
    else
        engine.operatorInterface[1]->disconnectFrom(engine.operatorInterface[0]);
    connected = !connected;
}