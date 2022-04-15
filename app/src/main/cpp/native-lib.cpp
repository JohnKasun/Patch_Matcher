#include <jni.h>
#include <string>
#include "AudioEngine.h"

AudioEngine engine;

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1connect(JNIEnv *env, jobject thiz,
                                                           jint connectable_a_id,
                                                           jint connectable_b_id) {

    int operatorIdA = connectable_a_id - 1;
    int operatorIdB = connectable_b_id - 1;
    if (operatorIdB == -1)
        engine.operatorInterface[operatorIdA].connectTo(&engine.outputTerminal);
    else
        engine.operatorInterface[operatorIdA].connectTo(&engine.operatorInterface[operatorIdB]);
    engine.parameterInterface[operatorIdA].operatorIds.insert(connectable_b_id);
    engine.initializeUserPatch();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1disconnect(JNIEnv *env, jobject thiz,
                                                              jint connectable_a_id,
                                                              jint connectable_b_id) {

    int operatorIdA = connectable_a_id - 1;
    int operatorIdB = connectable_b_id - 1;
    if (operatorIdB == -1)
        engine.operatorInterface[operatorIdA].disconnectFrom(&engine.outputTerminal);
    else
        engine.operatorInterface[operatorIdA].disconnectFrom(&engine.operatorInterface[operatorIdB]);
    engine.parameterInterface[operatorIdA].operatorIds.erase(connectable_b_id);
    engine.initializeUserPatch();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1onChangeFrequency(JNIEnv *env, jobject thiz,
                                                                     jint operator_id, jint value) {
    operator_id -= 1;
    engine.operatorInterface[operator_id].setFrequency(value);
    engine.parameterInterface[operator_id].fFreq = value;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1onChangeGain(JNIEnv *env, jobject thiz,
                                                                jint operator_id, jint value) {
    operator_id -= 1;
    engine.operatorInterface[operator_id].setGain(value);
    engine.parameterInterface[operator_id].fGain = value;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1onChangeFeedback(JNIEnv *env, jobject thiz,
                                                                    jint operator_id, jint value) {
    operator_id -= 1;
    float valueScaled = static_cast<float>(value) / 100.0f;
    engine.operatorInterface[operator_id].setFeedbackGain(valueScaled);
    engine.parameterInterface[operator_id].fFeedback = valueScaled;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1onWavetableChange(JNIEnv *env, jobject thiz,
                                                                     jint operator_id,
                                                                     jint wavetable_type) {
    operator_id -= 1;
    Wavetable::Wavetable_t eWaveType;
    switch (wavetable_type)
    {
        case 0:
            eWaveType = Wavetable::kSine;
            break;
        case 1:
            eWaveType = Wavetable::kSquare;
            break;
        case 2:
            eWaveType = Wavetable::kTriangle;
            break;
        case 3:
            eWaveType = Wavetable::kSaw;
            break;
        default:
            eWaveType = Wavetable::kCustom;
    }
    engine.changeWavetable(operator_id, eWaveType);
    engine.parameterInterface[operator_id].eWaveType = eWaveType;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1regenerateTarget(JNIEnv *env, jobject thiz) {
    engine.regenerateTarget();
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1getTargetValues(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(engine.getTargetValues().c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1resetValues(JNIEnv *env, jobject thiz,
                                                               jint operator_id) {

    operator_id -= 1;
    engine.operatorInterface[operator_id].reset();
    engine.parameterInterface[operator_id].fFreq = 0;
    engine.parameterInterface[operator_id].fGain = 0;
    engine.parameterInterface[operator_id].fFeedback = 0;
    engine.parameterInterface[operator_id].operatorIds.clear();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1onStopAudio(JNIEnv *env, jobject thiz) {
    engine.pauseAudio();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1onPlayTargetAudio(JNIEnv *env, jobject thiz) {
    engine.setOutputType(false);
    if (!engine.isRunning())
        engine.startAudio();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1onPlayUserAudio(JNIEnv *env, jobject thiz) {
    engine.setOutputType(true);
    if (!engine.isRunning())
        engine.startAudio();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1initializeUser(JNIEnv *env, jobject thiz) {
    engine.initializeUserPatch();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1onResetActivity(JNIEnv *env, jobject thiz) {
    engine.reset();
}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_johnkasun_patch_1matcher_GameActivity_ai_1onEvaluatePatch(JNIEnv *env, jobject thiz) {
    return engine.evaluatePatch();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1connect(JNIEnv *env, jobject thiz,
                                                           jint connectable_a_id,
                                                           jint connectable_b_id) {

    int operatorIdA = connectable_a_id - 1;
    int operatorIdB = connectable_b_id - 1;
    if (operatorIdB == -1)
        engine.operatorInterface[operatorIdA].connectTo(&engine.outputTerminal);
    else
        engine.operatorInterface[operatorIdA].connectTo(&engine.operatorInterface[operatorIdB]);
    engine.parameterInterface[operatorIdA].operatorIds.insert(connectable_b_id);
    engine.initializeUserPatch();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1disconnect(JNIEnv *env, jobject thiz,
                                                              jint connectable_a_id,
                                                              jint connectable_b_id) {

    int operatorIdA = connectable_a_id - 1;
    int operatorIdB = connectable_b_id - 1;
    if (operatorIdB == -1)
        engine.operatorInterface[operatorIdA].disconnectFrom(&engine.outputTerminal);
    else
        engine.operatorInterface[operatorIdA].disconnectFrom(&engine.operatorInterface[operatorIdB]);
    engine.parameterInterface[operatorIdA].operatorIds.erase(connectable_b_id);
    engine.initializeUserPatch();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1onChangeFrequency(JNIEnv *env, jobject thiz,
                                                                     jint operator_id, jint value) {
    operator_id -= 1;
    engine.operatorInterface[operator_id].setFrequency(value);
    engine.parameterInterface[operator_id].fFreq = value;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1onChangeGain(JNIEnv *env, jobject thiz,
                                                                jint operator_id, jint value) {
    operator_id -= 1;
    engine.operatorInterface[operator_id].setGain(value);
    engine.parameterInterface[operator_id].fGain = value;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1onChangeFeedback(JNIEnv *env, jobject thiz,
                                                                    jint operator_id, jint value) {
    operator_id -= 1;
    float valueScaled = static_cast<float>(value) / 100.0f;
    engine.operatorInterface[operator_id].setFeedbackGain(valueScaled);
    engine.parameterInterface[operator_id].fFeedback = valueScaled;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1onWavetableChange(JNIEnv *env, jobject thiz,
                                                                     jint operator_id,
                                                                     jint wavetable_type) {
    operator_id -= 1;
    Wavetable::Wavetable_t eWaveType;
    switch (wavetable_type)
    {
        case 0:
            eWaveType = Wavetable::kSine;
            break;
        case 1:
            eWaveType = Wavetable::kSquare;
            break;
        case 2:
            eWaveType = Wavetable::kTriangle;
            break;
        case 3:
            eWaveType = Wavetable::kSaw;
            break;
        default:
            eWaveType = Wavetable::kCustom;
    }
    engine.changeWavetable(operator_id, eWaveType);
    engine.parameterInterface[operator_id].eWaveType = eWaveType;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1regenerateTarget(JNIEnv *env, jobject thiz) {
    engine.regenerateTarget();
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1getTargetValues(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(engine.getTargetValues().c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1resetValues(JNIEnv *env, jobject thiz,
                                                               jint operator_id) {

    operator_id -= 1;
    engine.operatorInterface[operator_id].reset();
    engine.parameterInterface[operator_id].fFreq = 0;
    engine.parameterInterface[operator_id].fGain = 0;
    engine.parameterInterface[operator_id].fFeedback = 0;
    engine.parameterInterface[operator_id].operatorIds.clear();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1onStopAudio(JNIEnv *env, jobject thiz) {
    engine.pauseAudio();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1onPlayTargetAudio(JNIEnv *env, jobject thiz) {
    engine.setOutputType(false);
    if (!engine.isRunning())
        engine.startAudio();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1onPlayUserAudio(JNIEnv *env, jobject thiz) {
    engine.setOutputType(true);
    if (!engine.isRunning())
        engine.startAudio();
}


extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1initializeUser(JNIEnv *env, jobject thiz) {
    engine.initializeUserPatch();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1onResetActivity(JNIEnv *env, jobject thiz) {
    engine.reset();
}
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1onEvaluatePatch(JNIEnv *env, jobject thiz) {
    return engine.evaluatePatch();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_CampaignActivity_ai_1setLevel(JNIEnv *env, jobject thiz, jint level) {
    engine.setLevelPatch(level);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_johnkasun_patch_1matcher_TutorialActivity_ai_1setTutorialPatch(JNIEnv *env, jobject thiz) {
    engine.setTutorialPatch();
}