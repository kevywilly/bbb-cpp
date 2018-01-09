#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include<iostream>
#include<opencv2/opencv.hpp> 

using namespace std;
using namespace cv;

#define IMAGE_PATH "images"

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
        capture.open(0);
        if(!capture.isOpened()){   // connect to the camera
            cout << "Failed to connect to the camera." << endl;
        }

        Mat frame, gray, edges;    // images for orignal, grayscale and edge image
        capture >> frame;          // capture the image to the frame
        if(frame.empty()){         // did the capture succeed?
           cout << "Failed to capture an image" << endl;
           return -1;
        }
        cout << "Processing - Performing Image Processing" << endl;
        cvtColor(frame, gray, CV_BGR2GRAY); // convert to grayscale
        blur(gray, edges, Size(3,3));       // blur grayscale image 3x3 kernel
        // use Canny edge detector that outputs to the same image
        // low threshold = 10, high threshold = 30, kernel size = 3
        Canny(edges, edges, 10, 30, 3);      // Run Canny edge detector
        cout << "Finished Processing - Saving images" << endl;
    
        imwrite("images/capture.png", frame);
        imwrite("images/grayscale.png", gray);
        imwrite("images/edges.png", edges);
        
        release();
        return 0;
    }
    
    // Release the capture if in progress
    void release() { capture.release(); }
    
    // Set frame size
    void set_frame_size(int width, int height) {
        capture.set(CV_CAP_PROP_FRAME_WIDTH,width);   // width pixels
        capture.set(CV_CAP_PROP_FRAME_HEIGHT,height);   // height pixels
    }
    
    // Set gain
    void set_gain(int value) {
        capture.set(CV_CAP_PROP_GAIN, value);
    }
    
    virtual ~Camera() {
        release();
    }
    
private:
    VideoCapture capture;
   
};
#endif /* CAMERA_HPP_ */