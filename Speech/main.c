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
#include "vowels.h"


#define SAMPLE_RATE (22050) // Speech contains no relevant frequencies any higher
#define PI (3.141592654)
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
    char vowel;
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
    data->pitch = 1;
    
    FREQUENCY_ARRAY frequencies = getVowelFrequencies(data->vowel);
    for(i=0; i<framesPerBuffer; i++)
    {
        v = sin(i * frequencies.freq[0] * 2 * PI / SAMPLE_RATE);
        v += sin(i * frequencies.freq[1] * 2 * PI / SAMPLE_RATE);
        v += sin(i * frequencies.freq[2] * 2 * PI / SAMPLE_RATE);
        
        *out++ = v;
        
        *out *= .33;
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
    
    /* Have the sounds play for a second */
    data.vowel = 'a';
    Pa_Sleep(500);
    data.vowel = 'c';
    Pa_Sleep(100);

    data.vowel = 'A';
    Pa_Sleep(500);
    data.vowel = 'c';
    Pa_Sleep(100);
    
    data.vowel = 'e';
    Pa_Sleep(500);
    data.vowel = 'c';
    Pa_Sleep(100);
    
    data.vowel = 'E';
    Pa_Sleep(500);
    data.vowel = 'c';
    Pa_Sleep(100);
    
    data.vowel = 'i';
    Pa_Sleep(500);
    data.vowel = 'c';
    Pa_Sleep(100);
    
    data.vowel = 'I';
    Pa_Sleep(500);
    data.vowel = 'c';
    Pa_Sleep(100);
    
    data.vowel = 'o';
    Pa_Sleep(500);
    data.vowel = 'c';
    Pa_Sleep(100);
    
    data.vowel = 'O';
    Pa_Sleep(500);
    data.vowel = 'c';
    Pa_Sleep(100);
    
    data.vowel = 'u';
    Pa_Sleep(500);
    data.vowel = 'c';
    Pa_Sleep(100);
    
    data.vowel = 'U';
    Pa_Sleep(500);
    data.vowel = 'c';
    Pa_Sleep(100);
    
    
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
