#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <OpenCV/OpenCV.h>
#include "SinGen.h"

#define NUM_XSTEPS 10
#define NUM_YSTEPS 10

void pixelate(IplImage *gimg, float *vals)
{
	assert(NUM_XSTEPS * NUM_YSTEPS == NUM_WAVES);
  // get the image data
  int height    = gimg->height;
  int width     = gimg->width;
  int step      = gimg->widthStep;
  int channels  = gimg->nChannels;
  uchar *data      = (uchar *)gimg->imageData;
  
  unsigned perX = width / NUM_XSTEPS + 1;
  unsigned perY = height / NUM_YSTEPS + 1;

  // invert the image
  unsigned long long avgIntensity[NUM_XSTEPS * NUM_YSTEPS];
  memset(avgIntensity,0,NUM_XSTEPS * NUM_YSTEPS * sizeof(avgIntensity[0]));

  for(int i=0;i<height;i++){ 

    for(int j=0;j<width;j++){ 

      for(int k=0;k<channels;k++){

        uchar d = data[ i*step  +  j*channels  +  k];

        unsigned ycoord = (i / perY);
        unsigned xcoord = (j / perX);
        assert(xcoord < NUM_XSTEPS);
        assert(ycoord < NUM_YSTEPS);

        avgIntensity[ xcoord * NUM_XSTEPS + ycoord ] += d;
      }
    }
  }
  float favgIntensity[NUM_XSTEPS * NUM_YSTEPS];
  float segPixels = (float)(height * width) / (float)(NUM_XSTEPS * NUM_YSTEPS);
  //fprintf(stderr,"height = %u. width = %u. xs = %u. ys = %u. seg = %f\n",height,width,NUM_XSTEPS, NUM_YSTEPS,segPixels);
  for(int i = 0; i < NUM_XSTEPS * NUM_YSTEPS; i++ ){
	  
      //printf("%d: %llu divided by %f = %f\n",i,avgIntensity[i],segPixels,((float)avgIntensity[i])/segPixels);
      favgIntensity[i] = (float)avgIntensity[i]/segPixels;
	  vals[i] = favgIntensity[i] / 256.;
	  if(vals[i] < 0.0){ vals[i] = 0.0;}
	  if(vals[i] > 1.0){ vals[i] = 1.0;}
	  assert(vals[i] >= 0.0 && vals[i] <= 1.0);
	  
  } 

  for(int i=0;i<height;i++){ 
    for(int j=0;j<width;j++){ 
      for(int k=0;k<channels;k++){

        unsigned ycoord = (i / perY);
        unsigned xcoord = (j / perX);
        assert(xcoord < NUM_XSTEPS);
        assert(ycoord < NUM_YSTEPS);

        data[ i*step  +  j*channels  +  k] = favgIntensity[ xcoord * NUM_XSTEPS + ycoord ];
      }
    }
  }
}
