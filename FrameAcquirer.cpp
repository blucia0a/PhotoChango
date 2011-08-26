#include <OpenCV/OpenCV.h>
#include <cassert>
#include <iostream>
#include "Pixelator.h"
#include "FrameAcquirer.h"
#include "SinGen.h"

const char  * WINDOW_NAME  = "PhotoChango - Brandon Lucia 2011 - http://cs.washington.edu/homes/blucia0a - 'q' to quit";


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
    
    // be nice and return no error
    return;
}
