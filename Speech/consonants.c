//
//  consonants.c
//  Speech
//
//  Created by Gabrielle Unsworth on 2/21/17.
//  Copyright © 2017 Gabrielle Unsworth. All rights reserved.
//

#include "consonants.h"
#include "utils.h"

struct FREQUENCY_ARRAY getConsonantFrequencies(char token) {
    struct FREQUENCY_ARRAY arr;
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
        default:
            arr.freq[0] = 0;
            arr.freq[1] = 0;
            arr.freq[2] = 0;
    }
    
    return arr;
}
