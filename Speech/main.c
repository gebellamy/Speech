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
#include "consonants.h"
#include "utils.h"


void logPaError(PaError err) {
    printf("PortAudio error: %s\n", Pa_GetErrorText(err));
    return;
}

typedef struct
{
    /* A single-character token representing a single phoneme */
    char token;
    /* 1 if phoneme is a vowel, otherwise 0 */
    short isVowel;
    /* The voice onset time of a consonant */
    int vot;
    /* 1 if noise is needed, otherwise 0 */
    int fricationNoise;
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
    struct FREQUENCY_DATA frequencies = {};
    
    // TODO: Quit setting anything but the token, figure out a way to
    // get whether or not it's a vowel from tokenizer that doesn't exist
    // yet.
    if (data->isVowel) {
        frequencies = getVowelFrequencies(data->token);
    } else {
        frequencies = getConsonantFrequencies(data->token);
    }
    for(i=0; i<framesPerBuffer; i++)
    {
        v = sin(i * frequencies.freq[0] * 2 * PI / SAMPLE_RATE);
        v += sin(i * frequencies.freq[1] * 2 * PI / SAMPLE_RATE) * 0.45f;
        v += sin(i * frequencies.freq[2] * 2 * PI / SAMPLE_RATE) * 0.05f;
        
        if (data->fricationNoise) {
            v += getFricationNoise(i);
        }
        
//        v *= 0.5f;
        
        *out++ = v;
    }
    return 0;
}

void consonantTest(void *userData) {
    paTestData *data = (paTestData*)userData;
    
    /* Test a couple consonant sounds with the 'ah' vowel */
    data->token = 'l';
    data->isVowel = 0;
    Pa_Sleep(60);
    data->token = 'A';
    data->isVowel = 1;
    Pa_Sleep(300);
    data->token = 'l';
    data->isVowel = 0;
    Pa_Sleep(60);
    data->token = 'A';
    data->isVowel = 1;
    Pa_Sleep(300);
    data->token = ' ';
    Pa_Sleep(500);
    
    data->token = 's';
    data->isVowel = 0;
    data->fricationNoise = 1;
    Pa_Sleep(70);
    data->token = 'O';
    data->isVowel = 1;
    data->fricationNoise = 0;
    Pa_Sleep(300);
}

void vowelTest(void *userData) {
    paTestData *data = (paTestData*)userData;
    
    /* Have the sounds play for a second */
    data->token = 'a';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
    
    data->token = 'A';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
    
    data->token = 'e';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
    
    data->token = 'E';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
    
    data->token = 'i';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
    
    data->token = 'I';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
    
    data->token = 'o';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
    
    data->token = 'O';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
    
    data->token = 'u';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
    
    data->token = 'U';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
    
    data->token = 'y';
    data->isVowel = 1;
    Pa_Sleep(500);
    data->token = ' ';
    Pa_Sleep(100);
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

//    vowelTest(&data);
    consonantTest(&data);
    
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
