#include "camera/Camera.h"
#include "network/SocketServer.h"
#include<iostream>

using namespace std;

#define CAMERA_FRAME_WIDTH 640
#define CAMERA_FRAME_HEIGHT 480
#define TCP_PORT 54321

int main()
{
    
    // ======= CAMERA ===========
    cout << "fetching Camera" << endl;
    Camera camera(0, CAMERA_FRAME_WIDTH, CAMERA_FRAME_HEIGHT);
    
    cout << "grabbing Image" << endl;
    cout << camera.grab_bw() << endl;
    
    
    // ======= SERVO ==============
    // ======= TCP SERVER =========
    
    cout << "Starting EBB Server Example" << endl;
    SocketServer server(54321);
    cout << "Listening for a connection..." << endl;
    server.listen();
    string rec = server.receive(1024);
    cout << "Received from the client [" << rec << "]" << endl;
    string message("The Server says thanks!");
    cout << "Sending back [" << message << "]" << endl;
    server.send(message);
    cout << "End of EBB Server Example" << endl;
   
    
    /*
    VideoCapture capture(0);   // capturing from /dev/video0

    cout << "Started Processing - Capturing Image" << endl;
    // set any  properties in the VideoCapture object
    capture.set(CV_CAP_PROP_FRAME_WIDTH,1280);   // width pixels
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,720);   // height pixels
    capture.set(CV_CAP_PROP_GAIN, 0);            // Enable auto gain etc.
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

    imwrite("capture.png", frame);
    imwrite("grayscale.png", gray);
    imwrite("edges.png", edges);
    */
    return 0;
}