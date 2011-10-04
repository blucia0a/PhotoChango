#ifndef _SIN_GEN_H_
#define _SIN_GEN_H_
/*
 *  SinGen.h
 *  Sin
 *
 *  Created by blucia0a on 8/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

//#include <Cocoa/Cocoa.h>
#include <CoreAudio/AudioHardware.h>
#include "Wave.h"
#include "SampleMixer.h"
#include "tones.h"

#define NUM_WAVES 100
static float tones[NUM_WAVES] = { Asharp3, Asharp3, C3, C3, D3, D3, Dsharp3, Dsharp3,  
                                  Asharp3, Asharp3, C3, C3, D3, D3, Dsharp3, Dsharp3,  
	                              
	                              F3, F3, G3, G3, A4, A4, Asharp3, Asharp3, Csharp3, Csharp3, C4, C4,
	                              F3, F3, G3, G3, A4, A4, Asharp3, Asharp3, Csharp3, Csharp3, C4, C4,
	                      
				      D4, D4, Dsharp4, Dsharp4, F4, F4, G4, G4, A5, A5,
	                              D4, D4, Dsharp4, Dsharp4, F4, F4, G4, G4, A5, A5,
	
	                              Asharp5, Asharp5, C5, C5, D5, D5, Dsharp5, Dsharp5, F5, F5,
	                              Asharp5, Asharp5, C5, C5, D5, D5, Dsharp5, Dsharp5, F5, F5,
	
	                              G5, G5, A6, A6, Asharp6, Asharp6, C6, C6, D6, D6, 
	                              G5, G5, A6, A6, Asharp6, Asharp6, C6, C6, D6, D6};

class SinGen {

public:	
	
	Boolean		initialized;	// successful init?
	Boolean		soundPlaying;	// playing now?
	AudioDeviceID	device;		// the default device
	UInt32	deviceBufferSize;	// bufferSize returned by kAudioDevicePropertyBufferSize
	AudioStreamBasicDescription	deviceFormat;	// info about the default device
    double pan, panz;
	SampleMixer *mix;
	
	SinGen();
	void setup();
	bool sstart();
	bool sstop();
	void setAmplitudes(float *vals);
	void setFrequencies(float *vals);
	
	Wave *waves[NUM_WAVES];
	
	
};

#endif
