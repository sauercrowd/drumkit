// Copyright 2019 Jonas Otten
#include <portaudio.h>
#include <cinttypes>
#include <iostream>

typedef struct {
    float left_phase;
    float right_phase;
} paTestData;


static int patestCallback(const void *inputBuffer,
               void *outputBuffer,
               int64_t framesPerBuffer,
               const PaStreamCallbackTimeInfo* timeInfo,
               PaStreamCallbackFlags statusFlags,
               void *userData) {
    paTestData *data = static_cast<paTestData*>(userData);
    float *out = static_cast<float*>(outputBuffer);
    (void) inputBuffer;
    unsigned int i;

    for (i=0; i < framesPerBuffer; i++) {
        *out++ = data->left_phase;
        *out++ = data->right_phase;
        data->left_phase += 0.01f;
        if (data->left_phase >= 1.0f)
            data->left_phase -= 2.0f;
        if (data->right_phase >= 1.0f)
            data->right_phase -= 2.0f;
    }
}


int main(int argc, char** argv) {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cout << "PortAudio error:" << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    err = Pa_Terminate();
    if (err != paNoError) {
        std::cout << "PortAudio error:" << Pa_GetErrorText(err) << std::endl;
        return -1;
    }
    return 0;
}
