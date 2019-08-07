// Copyright 2019 Jonas Otten
#include <portaudio.h>
#include <cinttypes>
#include <iostream>

#define SAMPLE_RATE (44100)

typedef struct {
    float left_phase;
    float right_phase;
} paTestData;

static paTestData testData;

static int patestCallback(const void *inputBuffer,
               void *outputBuffer,
               unsigned long framesPerBuffer,  // NOLINT 4
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
        std::cerr << "PortAudio error:" << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    PaStream *stream;

    err = Pa_OpenDefaultStream(&stream,
            0,  // no input
            2,  // stereo output
            paFloat32,  // 32 bit floating point output
            SAMPLE_RATE,
            256,  // frames per buffer
            patestCallback,
            &testData);
    if (err != paNoError) {
        std::cerr << "PortAudio error:" << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error:" << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    Pa_Sleep(20*1000);

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error:" << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "PortAudio error:" << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    return 0;
}
