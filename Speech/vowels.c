//
//  vowels.c
//  Speech
//
//  Created by Gabrielle Unsworth on 2/21/17.
//  Copyright © 2017 Gabrielle Unsworth. All rights reserved.
//

#include <stdio.h>
#include "vowels.h"
#include "utils.h"

struct FREQUENCY_DATA getVowelFrequencies(char token) {
    struct FREQUENCY_DATA arr;
    switch(token) {
        case 'a': // cat
            arr.freq[0] = 800;
            arr.freq[1] = 1760;
            arr.freq[2] = 2500;
            break;
        case 'A': {// father
            arr.freq[0] = 710;
            arr.freq[1] = 1100;
            arr.freq[2] = 2450;
            break;
        }
        case 'e': //bet
            arr.freq[0] = 560;
            arr.freq[1] = 1480;
            arr.freq[2] = 2520;
            break;
        case 'E': // but
            arr.freq[0] = 760;
            arr.freq[1] = 1320;
            arr.freq[2] = 2500;
            break;
        case 'i': // hid
            arr.freq[0] = 360;
            arr.freq[1] = 2220;
            arr.freq[2] = 2960;
            break;
        case 'I': // heed
            arr.freq[0] = 280;
            arr.freq[1] = 2620;
            arr.freq[2] = 3380;
            break;
        case 'o': // cot
            arr.freq[0] = 560;
            arr.freq[1] = 920;
            arr.freq[2] = 2560;
            break;
        case 'O': // caught
            arr.freq[0] = 480;
            arr.freq[1] = 760;
            arr.freq[2] = 2620;
            break;
        case 'u': // put
            arr.freq[0] = 380;
            arr.freq[1] = 940;
            arr.freq[2] = 2300;
            break;
        case 'U': // boot
            arr.freq[0] = 320;
            arr.freq[1] = 920;
            arr.freq[2] = 2200;
            break;
        case 'y': // boat, I needed a symbol, okay?
            arr.freq[0] = 400;
            arr.freq[1] = 800;
            arr.freq[2] = 2600;
            break;
        default: // Let's default to silence
            arr.freq[0] = 0;
            arr.freq[1] = 0;
            arr.freq[2] = 0;
    }
    arr.isVowel = 1;
    
    return arr;
}
