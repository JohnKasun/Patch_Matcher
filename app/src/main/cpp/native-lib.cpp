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
Java_com_example_patch_1matcher_MainActivity_connectOperators(JNIEnv *env, jobject thiz,
                                                              jint operator_a, jint operator_b) {
    int operatorA_index = operator_a - 1;
    int operatorB_index = operator_b - 1;
    engine.operatorInterface[operatorA_index]->connectTo(engine.operatorInterface[operatorB_index]);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_patch_1matcher_MainActivity_disconnectOperators(JNIEnv *env, jobject thiz,
                                                                 jint operator_a, jint operator_b) {
    int operatorA_index = operator_a - 1;
    int operatorB_index = operator_b - 1;
    engine.operatorInterface[operatorA_index]->disconnectFrom(engine.operatorInterface[operatorB_index]);
}