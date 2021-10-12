//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_AUDIOENGINE_H
#define PATCH_MATCHER_AUDIOENGINE_H
#include <oboe/Oboe.h>


class AudioEngine : public oboe::AudioStreamCallback{
public:
    AudioEngine();
    virtual ~AudioEngine() = default;
    int32_t startAudio();
    void stopAudio();
    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override;
private:
};


#endif //PATCH_MATCHER_AUDIOENGINE_H
