#include <OpenCV/OpenCV.h>
#include <cassert>
#include <iostream>
#include "Pixelator.h"
#include "FrameAcquirer.h"
#include "SinGen.h"

const char  * WINDOW_NAME  = "PhotoChango - Brandon Lucia 2011 - http://cs.washington.edu/homes/blucia0a - 'q' to quit";
extern bool useMotion;
extern bool useMotionAndLight;

FrameAcquirer::FrameAcquirer(SinGen *s) 
{
	this->sg = s;
    
    // create all necessary instances
    cvNamedWindow (WINDOW_NAME, CV_WINDOW_AUTOSIZE);
    CvCapture * camera = cvCreateCameraCapture (CV_CAP_ANY);
    CvMemStorage* storage = cvCreateMemStorage(0);
    assert (storage);

    // you do own an iSight, don't you ?!?
    if (! camera)
        abort ();


    if(useMotion == false){
      // get an initial frame and duplicate it for later work
      IplImage *  current_frame = cvQueryFrame (camera);
      IplImage *  gray_image    = cvCreateImage(cvSize (current_frame->width, current_frame->height), IPL_DEPTH_8U, 1);
      assert (current_frame && gray_image);
      
      // as long as there are images ...
      while (current_frame = cvQueryFrame (camera))
      {
  	
          // convert to gray and downsize
        cvCvtColor (current_frame, gray_image, CV_BGR2GRAY);
          
  	float vals[NUM_WAVES];
  	pixelate(gray_image,vals);
  	this->sg->setAmplitudes(vals);
         
  
          // just show the image
          cvShowImage (WINDOW_NAME, gray_image);
  
          // cvShowImage (WINDOW_NAME, current_frame);
          // wait a tenth of a second for keypress and window drawing
          int key = cvWaitKey (30);
          if (key == 'q' || key == 'Q')
              break;
      }

    }else{

      IplImage *  current_frame = cvQueryFrame (camera);
      IplImage *  gray_image    = cvCreateImage(cvSize (current_frame->width, current_frame->height), IPL_DEPTH_8U, 1);
      IplImage *  avg_img = cvCreateImage(cvSize (current_frame->width, current_frame->height), IPL_DEPTH_32F, 1);
      IplImage *  gavg_img = cvCreateImage(cvSize (current_frame->width, current_frame->height), IPL_DEPTH_8U, 1);
      IplImage *  diff_img = cvCreateImage(cvSize (current_frame->width, current_frame->height), IPL_DEPTH_8U, 1);
      IplImage *  diff_img2 = cvCreateImage(cvSize (current_frame->width, current_frame->height), IPL_DEPTH_8U, 1);
      IplImage *  diff_img3 = cvCreateImage(cvSize (current_frame->width, current_frame->height), IPL_DEPTH_8U, 1);
      
      // as long as there are images ...
      while (current_frame = cvQueryFrame (camera))
      {
  
          // convert to gray and downsize
          cvCvtColor (current_frame, gray_image, CV_BGR2GRAY);
  
          cvSmooth( gray_image, gray_image);
          
          cvRunningAvg( gray_image, avg_img, .200, NULL);
  
          cvConvert( avg_img, gavg_img );
  
          cvAbsDiff( gray_image, gavg_img, diff_img );    

       
          cvConvert( diff_img, diff_img2 );

  	  float vals[NUM_WAVES];
          pixelate(diff_img,vals);
  	  this->sg->setAmplitudes(vals);

          if(useMotionAndLight){
            pixelate(gray_image,vals);
            for(int i = 0; i < NUM_WAVES; i++){
              vals[i] *= C8;
            }
  	    this->sg->setFrequencies(vals);
          }
          
          cvAddWeighted( diff_img2, 0.5, gray_image, 0.5, 0.5, diff_img);

          cvShowImage ( WINDOW_NAME, diff_img);

          int key = cvWaitKey (30);
          if (key == 'q' || key == 'Q')
              break;
      }
  
    }
    
    // be nice and return no error
    return;
}
