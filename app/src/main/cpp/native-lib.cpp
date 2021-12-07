#include <jni.h>
#include <string>
#include "AudioEngine.h"

AudioEngine engine;

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
JNIEXPORT jboolean JNICALL
Java_com_example_patch_1matcher_MainActivity_onFeedbackButtonPress(JNIEnv *env, jobject thiz) {
    static bool enabled{false};
    if (!enabled)
        engine.operatorInterface[0]->connectTo(engine.operatorInterface[0]);
    else
        engine.operatorInterface[0]->disconnectFrom(engine.operatorInterface[0]);
    enabled = !enabled;
    return enabled;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_patch_1matcher_MainActivity_onConnectButtonPress(JNIEnv *env, jobject thiz) {
    static bool connected{false};
    if (!connected)
        engine.operatorInterface[1]->connectTo(engine.operatorInterface[0]);
    else
        engine.operatorInterface[1]->disconnectFrom(engine.operatorInterface[0]);
    connected = !connected;
    return connected;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_patch_1matcher_MainActivity_onResetButtonPress(JNIEnv *env, jobject thiz) {
    engine.reset();
}