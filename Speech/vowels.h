//
//  vowels.h
//  Speech
//
//  Created by Gabrielle Unsworth on 2/21/17.
//  Copyright © 2017 Gabrielle Unsworth. All rights reserved.
//

#ifndef vowels_h
#define vowels_h

typedef struct {
    int freq[3];
} FREQUENCY_ARRAY;

FREQUENCY_ARRAY getVowelFrequencies(char token);

#endif /* vowels_h */
