//
//  consonants.c
//  Speech
//
//  Created by Gabrielle Unsworth on 2/21/17.
//  Copyright © 2017 Gabrielle Unsworth. All rights reserved.
//

#include <math.h>
#include "consonants.h"
#include "utils.h"

struct FREQUENCY_DATA getConsonantFrequencies(char token) {
    struct FREQUENCY_DATA arr;
    switch(token) {
        case 'l':
            arr.freq[0] = 450;
            arr.freq[1] = 1150;
            arr.freq[2] = 2600;
            break;
        case 'p':
            arr.freq[0] = 150;
            arr.freq[1] = 200;
            arr.freq[2] = 250;
            break;
        case 's':
            arr.fricationNoise = 1;
            arr.freq[0] = 0;
            arr.freq[1] = 0;
            arr.freq[2] = 0;
            break;
        default:
            arr.freq[0] = 0;
            arr.freq[1] = 0;
            arr.freq[2] = 0;
    }
    arr.isVowel = 0;
    
    return arr;
}

float getFricationNoise(int f) {
    float noise = 0.0;
    for (int i = 1000; i < 4000; i += 50) {
        noise += sin(f * i * 2 * PI / SAMPLE_RATE);
    }
    noise *= .05;
    
    return noise;
}
