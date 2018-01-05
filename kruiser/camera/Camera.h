#ifndef CAMERA_H_
#define CAMERA_H_

#include<iostream>
#include<opencv2/opencv.hpp>   // C++ OpenCV include file



using namespace cv;            // using the cv namespace too

class Camera {

private:
    VideoCapture capture;

public:
    // Constructor
	Camera(int deviceId, int width, int height);
	
	// Grab Black and White Image
    int grab_bw();
    
    // Set Width and Height
    void set_frame_size(int width, int height);
    
    // Set gain
    void set_gain(int value);
};


#endif /* CAMERA_H_ */
