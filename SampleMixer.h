#ifndef _SAMPLE_MIXER_H_
#define _SAMPLE_MIXER_H_
/*
 *  SampleMixer.h
 *  Sin
 *
 *  Created by blucia0a on 8/6/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "SampleSource.h"
class SampleMixer{
public:
	void Mix(int numSources, SampleSource **srcs, float *out);
};
#endif