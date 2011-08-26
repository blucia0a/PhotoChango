/*
 *  SinGen.cpp
 *  Sin
 *
 *  Created by blucia0a on 8/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "SampleMixer.h"
#include "Wave.h"
#include "SinGen.h"
#include "tones.h"
// this is the audio processing callback.
OSStatus sappIOProc (AudioDeviceID  inDevice, const AudioTimeStamp*  inNow, const AudioBufferList*   inInputData, 
					 const AudioTimeStamp*  inInputTime, AudioBufferList*  outOutputData, const AudioTimeStamp* inOutputTime, 
					 void* defptr)
{    
    SinGen *def = (SinGen*)defptr; // get access to Sinewave's data
    int i;
    
    int numSamples = def->deviceBufferSize / def->deviceFormat.mBytesPerFrame;
    
    // assume floats for now....
    float *out = (float*)outOutputData->mBuffers[0].mData;
    
    for (i=0; i<numSamples; ++i) {
        
        // write output
		//def->waves[0]->getNextSample(out);
		def->mix->Mix(NUM_WAVES,(SampleSource **)def->waves,out);
		
		out[0] = out[0] * (1.0 - def->panz);
		out[1] = out[1] * def->panz;
		
		//move the output pointer ahead in the hardware buffer
		out++; out++;
		
		//update the zippered pan value
        def->panz  = 0.001 * def->pan  + 0.999 * def->panz;
        
    }
    
    return kAudioHardwareNoError;     
}


/*SinGen Implementation*/
SinGen::SinGen(){
	this->mix = new SampleMixer();
}

void SinGen::setAmplitudes(float *amps){
	for(int i = 0; i < NUM_WAVES; i++){
	    this->waves[i]->setAmpVal(amps[i]);
	}
}

void SinGen::setup(void){
	
    OSStatus			err = kAudioHardwareNoError;
    UInt32				count;    
    device = kAudioDeviceUnknown;
	
    initialized = false;
	
    // get the default output device for the HAL
    count = sizeof(device);		// it is required to pass the size of the data to be returned
    err = AudioHardwareGetProperty(kAudioHardwarePropertyDefaultOutputDevice,  &count, (void *) &device);
    if (err != kAudioHardwareNoError) {
    	fprintf(stderr, "get kAudioHardwarePropertyDefaultOutputDevice error %ld\n", err);
        return;
    }
    
    // get the buffersize that the default device uses for IO
    count = sizeof(deviceBufferSize);	// it is required to pass the size of the data to be returned
    err = AudioDeviceGetProperty(device, 0, false, kAudioDevicePropertyBufferSize, &count, &deviceBufferSize);
    if (err != kAudioHardwareNoError) {
    	fprintf(stderr, "get kAudioDevicePropertyBufferSize error %ld\n", err);
        return;
    }
    fprintf(stderr, "deviceBufferSize = %ld\n", deviceBufferSize);
	
    // get a description of the data format used by the default device
    count = sizeof(deviceFormat);	// it is required to pass the size of the data to be returned
    err = AudioDeviceGetProperty(device, 0, false, kAudioDevicePropertyStreamFormat, &count, &deviceFormat);
    if (err != kAudioHardwareNoError) {
    	fprintf(stderr, "get kAudioDevicePropertyStreamFormat error %ld\n", err);
        return;
    }
    if (deviceFormat.mFormatID != kAudioFormatLinearPCM) {
    	fprintf(stderr, "mFormatID !=  kAudioFormatLinearPCM\n");
        return;
    }
    if (!(deviceFormat.mFormatFlags & kLinearPCMFormatFlagIsFloat)) {
    	fprintf(stderr, "Sorry, currently only works with float format....\n");
        return;
    }
    
    initialized = true;
	
    for(int i = 0; i < NUM_WAVES; i++){
        waves[i] = new Wave(tones[i],(double)deviceFormat.mSampleRate,0.5);	
	}
	this->panz = this->pan = 0.5;
	
    fprintf(stderr, "mSampleRate = %g\n", deviceFormat.mSampleRate);
    fprintf(stderr, "mFormatFlags = %08lX\n", deviceFormat.mFormatFlags);
    fprintf(stderr, "mBytesPerPacket = %ld\n", deviceFormat.mBytesPerPacket);
    fprintf(stderr, "mFramesPerPacket = %ld\n", deviceFormat.mFramesPerPacket);
    fprintf(stderr, "mChannelsPerFrame = %ld\n", deviceFormat.mChannelsPerFrame);
    fprintf(stderr, "mBytesPerFrame = %ld\n", deviceFormat.mBytesPerFrame);
    fprintf(stderr, "mBitsPerChannel = %ld\n", deviceFormat.mBitsPerChannel);

}


bool SinGen::sstart(){
	
    OSStatus		err = kAudioHardwareNoError;
	
    if (!initialized) return false;
    if (soundPlaying) return false;
    
    err = AudioDeviceAddIOProc(device, sappIOProc, (void *) this);	// setup our device with an IO proc
    if (err != kAudioHardwareNoError) return false;
    
    err = AudioDeviceStart(device, sappIOProc);				// start playing sound through the device
    if (err != kAudioHardwareNoError) return false;
	
    soundPlaying = true;						// set the playing status global to true
    return true;

}

bool SinGen::sstop(){
	
    OSStatus 	err = kAudioHardwareNoError;
    
    if (!initialized) return false;
    if (!soundPlaying) return false;
    
    err = AudioDeviceStop(device, sappIOProc);				// stop playing sound through the device
    if (err != kAudioHardwareNoError) return false;
	
    err = AudioDeviceRemoveIOProc(device, sappIOProc);			// remove the IO proc from the device
    if (err != kAudioHardwareNoError) return false;
    
    soundPlaying = false;						// set the playing status global to false
    return true;
	
}
