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
Java_com_example_patch_1matcher_MainActivity_connect_1AudioEngine(JNIEnv *env, jobject thiz,
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
Java_com_example_patch_1matcher_MainActivity_disconnect_1AudioEngine(JNIEnv *env, jobject thiz,
                                                                     jint connectable_a_id,
                                                                     jint connectable_b_id) {
    connectable_a_id -= 1;
    connectable_b_id -= 1;

    if (connectable_b_id < 0)
        engine.operatorInterface[connectable_a_id]->disconnectFrom(&engine.outputTerminal);
    else
        engine.operatorInterface[connectable_a_id]->disconnectFrom(engine.operatorInterface[connectable_b_id]);
}