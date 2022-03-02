#include <jni.h>
#include <string>
#include "AudioEngine.h"

AudioEngine engine;

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1connect(JNIEnv *env, jobject thiz,
                                                           jint connectable_a_id,
                                                           jint connectable_b_id) {


    engine.parameterInterface[connectable_a_id-1]->operatorIds.insert(connectable_b_id);
    engine.reinitializeUserPatch();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1disconnect(JNIEnv *env, jobject thiz,
                                                              jint connectable_a_id,
                                                              jint connectable_b_id) {

    engine.parameterInterface[connectable_a_id=1]->operatorIds.erase(connectable_b_id);
    engine.reinitializeUserPatch();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1onChangeFrequency(JNIEnv *env, jobject thiz,
                                                                     jint operator_id, jint value) {
    operator_id -= 1;
    engine.operatorInterface[operator_id]->setFrequency(value);
    engine.parameterInterface[operator_id]->fFreq = value;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1onChangeGain(JNIEnv *env, jobject thiz,
                                                                jint operator_id, jint value) {
    operator_id -= 1;
    float valueScaled = static_cast<float>(value);
    engine.operatorInterface[operator_id]->setGain(valueScaled);
    engine.parameterInterface[operator_id]->fGain = valueScaled;

}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1onChangeFeedback(JNIEnv *env, jobject thiz,
                                                                    jint operator_id, jint value) {
    operator_id -= 1;
    float valueScaled = static_cast<float>(value) / 100.0f;
    engine.operatorInterface[operator_id]->setFeedbackGain(valueScaled);
    engine.parameterInterface[operator_id]->fFeedback = valueScaled;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1resetValues(JNIEnv *env, jobject thiz,
                                                               jint operator_id) {
    operator_id -= 1;
    engine.operatorInterface[operator_id]->reset();
    engine.parameterInterface[operator_id]->fFreq = 0;
    engine.parameterInterface[operator_id]->fGain = 0;
    engine.parameterInterface[operator_id]->fFeedback = 0;
    engine.parameterInterface[operator_id]->operatorIds.clear();
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

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1onWavetableChange(JNIEnv *env, jobject thiz,
                                                                     jint operator_id,
                                                                     jint wavetable_type) {
    operator_id -= 1;
    engine.changeWavetable(operator_id, wavetable_type);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1regenerateTarget(JNIEnv *env, jobject thiz) {
    engine.regenerateTarget();
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_johnkasun_patch_1matcher_MainActivity_ai_1getTargetValues(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(engine.getTargetValues().c_str());
}