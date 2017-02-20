//
//  main.c
//  Speech
//
//  Created by Gabrielle Unsworth on 2/20/17.
//  Copyright © 2017 Gabrielle Unsworth. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "../../portaudio/include/portaudio.h"

#define SAMPLE_RATE (22050) // Speech contains no relevant frequencies any higher
#define PI (3.141592653)
#define F1 (530)
#define F2 (1850)
#define F3 (2500)

void logPaError(PaError err) {
    printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    return;
}

typedef struct
{
    float pitch;
} paTestData;

static int playSound( const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData )
{
    /* Cast data passed through stream to our structure. */
    paTestData *data = (paTestData*)userData;
    float *out = (float*)outputBuffer;
    unsigned int i;
    (void) inputBuffer; /* Prevent unused variable warning. */
    float v;
//    int freq = F1;
    data->pitch = 1;
    
    for(i=0; i<framesPerBuffer; i++)
    {
        v = sin(i * F1 * 2 * PI / SAMPLE_RATE);
        v += sin(i * F2 * 2 * PI / SAMPLE_RATE);
        v += sin(i * F3 * 2 * PI / SAMPLE_RATE);
        
        *out++ = v;
        
        *out *= .3;
        
        data->pitch += 1;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        logPaError(err);
        return 1;
    }
    
    static paTestData data;
    PaStream *stream;
    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream( &stream,
                               0,          /* no input channels */
                               1,          /* mono output */
                               paFloat32,  /* 32 bit floating point output */
                               SAMPLE_RATE,
                               256,        /* frames per buffer, i.e. the number
                                            of sample frames that PortAudio will
                                            request from the callback. Many apps
                                            may want to use
                                            paFramesPerBufferUnspecified, which
                                            tells PortAudio to pick the best,
                                            possibly changing, buffer size.*/
                               playSound, /* this is your callback function */
                               &data ); /*This is a pointer that will be passed to
                                         your callback*/
    if(err != paNoError) {
        logPaError(err);
        return 1;
    }
    
    /* Start an audio stream */
    err = Pa_StartStream(stream);
    if(err != paNoError) {
        logPaError(err);
        return 1;
    }
    
    /* Have the sound play for a second */
    Pa_Sleep(1000);
    
    /* Stop the audio stream */
    err = Pa_StopStream(stream);
    if(err != paNoError) {
        logPaError(err);
        return 1;
    }

    /* Close the audio stream to free up resources */
    err = Pa_CloseStream(stream);
    if(err != paNoError) {
        logPaError(err);
        return 1;
    }
    
    /* Stop PortAudio */
    err = Pa_Terminate();
    if (err != paNoError) {
        logPaError(err);
        return 1;
    }
    return 0;
}
