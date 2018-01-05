#include "Camera.h"
#include<iostream>
#include<opencv2/opencv.hpp> 

using namespace std;
using namespace cv;

// Constructor
Camera::Camera(int deviceId, int width, int height) : capture(deviceId) {
	
	// set the frame size
	set_frame_size(width, height);
	// set prop gain
    set_gain(0);            // Enable auto gain etc.
}


// Grab BW Image
int Camera::grab_bw(){
    return 0;
}

void Camera::set_frame_size(int width, int height) {
    capture.set(CV_CAP_PROP_FRAME_WIDTH,width);   // width pixels
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,height);   // height pixels
}

void Camera::set_gain(int value) {
    capture.set(CV_CAP_PROP_GAIN, value);
}
   