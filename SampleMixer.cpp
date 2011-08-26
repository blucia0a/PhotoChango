/*
 *  SampleMixer.cpp
 *  Sin
 *
 *  Created by blucia0a on 8/6/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "SampleMixer.h"

void SampleMixer::Mix(int numSources, SampleSource **srcs, float *out){
	
	out[0] = 0.0; //left
	out[1] = 0.0; //right
	for(int i = 0; i < numSources; i++){
		float o[2];
	    srcs[i]->getNextSample(o);
		out[0] = out[0] + o[0];// > 1.0 ? 0.9 : out[0] + o[0];
		out[1] = out[1] + o[1];// > 1.0 ? 0.9 : out[1] + o[1];
	}
	out[0] /= (float)numSources;
	out[1] /= (float)numSources;

	
}
