#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include<iostream>
#include<opencv2/opencv.hpp> 

using namespace std;
using namespace cv;

class Camera {

public:
    // Constructor
    Camera(int deviceId, int width, int height) : capture(deviceId) {
    	
    	// set the frame size
    	set_frame_size(width, height);
    	// set prop gain
        set_gain(0);            // Enable auto gain etc.
    }
    
    
    // Grab BW Image
    int grab_bw(){
        cout << "Grabbing Black and White Image" << endl;
        return 0;
    }
    
    void set_frame_size(int width, int height) {
        capture.set(CV_CAP_PROP_FRAME_WIDTH,width);   // width pixels
        capture.set(CV_CAP_PROP_FRAME_HEIGHT,height);   // height pixels
    }
    
    void set_gain(int value) {
        capture.set(CV_CAP_PROP_GAIN, value);
    }
    
private:
    VideoCapture capture;
   
};
#endif /* CAMERA_HPP_ */