#include <jni.h>
#include <string>
#include "AudioEngine.h"

AudioEngine engine;

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1connect(JNIEnv *env, jobject thiz,
                                                           jint connectable_a_id,
                                                           jint connectable_b_id) {
    connectable_a_id -= 1;
    connectable_b_id -= 1;

    if (connectable_b_id < 0)
        engine.operatorInterface[connectable_a_id]->connectTo(&engine.outputTerminal);
    else
        engine.operatorInterface[connectable_a_id]->connectTo(engine.operatorInterface[connectable_b_id]);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1disconnect(JNIEnv *env, jobject thiz,
                                                              jint connectable_a_id,
                                                              jint connectable_b_id) {
    connectable_a_id -= 1;
    connectable_b_id -= 1;

    if (connectable_b_id < 0)
        engine.operatorInterface[connectable_a_id]->disconnectFrom(&engine.outputTerminal);
    else
        engine.operatorInterface[connectable_a_id]->disconnectFrom(engine.operatorInterface[connectable_b_id]);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1onChangeFrequency(JNIEnv *env, jobject thiz,
                                                                     jint operator_id, jint value) {
    operator_id -= 1;

    engine.operatorInterface[operator_id]->setFrequency(value);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1onChangeGain(JNIEnv *env, jobject thiz,
                                                                jint operator_id, jint value) {
    operator_id -= 1;

    float valueScaled = static_cast<float>(value) / 100.0f;
    engine.operatorInterface[operator_id]->setGain(valueScaled);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1onChangeFeedback(JNIEnv *env, jobject thiz,
                                                                    jint operator_id, jint value) {
    operator_id -= 1;

    float valueScaled = static_cast<float>(value) / 100.0f;
    engine.operatorInterface[operator_id]->setFeedbackGain(valueScaled);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1resetValues(JNIEnv *env, jobject thiz,
                                                               jint operator_id) {
    operator_id -= 1;
    engine.operatorInterface[operator_id]->setFrequency(0.0);
    engine.operatorInterface[operator_id]->setGain(0.0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1onStopAudio(JNIEnv *env, jobject thiz) {
    engine.pauseAudio();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1onPlayTargetAudio(JNIEnv *env, jobject thiz) {
    engine.setOutputType(false);
    if (!engine.isRunning())
        engine.startAudio();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1onPlayUserAudio(JNIEnv *env, jobject thiz) {
    engine.setOutputType(true);
    if (!engine.isRunning())
        engine.startAudio();
}
