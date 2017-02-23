//
//  utils.h
//  Speech
//
//  Created by Gabrielle Unsworth on 2/21/17.
//  Copyright © 2017 Gabrielle Unsworth. All rights reserved.
//

#ifndef utils_h
#define utils_h

#define SAMPLE_RATE (22050) // Speech contains no relevant frequencies any higher
#define PI (3.141592654)

struct FREQUENCY_DATA {
    int freq[3];
    int isVowel;
    int fricationNoise;
};

#endif /* utils_h */
