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
static float tones[NUM_WAVES] = { A3, A3, B3, B3, C3, C3, D3, D3, E3, E3,
                                  A3, A3, B3, B3, C3, C3, D3, D3, E3, E3,
	                              
	                              F3, F3, G3, G3, A4, A4, B4, B4, C4, C4,
	                              F3, F3, G3, G3, A4, A4, B4, B4, C4, C4,
	                      
								  D4, D4, E4, E4, F4, F4, G4, G4, A5, A5,
	                              D4, D4, E4, E4, F4, F4, G4, G4, A5, A5,
	
	                              B5, B5, C5, C5, D5, D5, E5, E5, F5, F5,
	                              B5, B5, C5, C5, D5, D5, E5, E5, F5, F5,
	
	                              G5, G5, A6, A6, B6, B6, C6, C6, D6, D6, 
	                              G5, G5, A6, A6, B6, B6, C6, C6, D6, D6};

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
	
	Wave *waves[NUM_WAVES];
	
	
};

#endif