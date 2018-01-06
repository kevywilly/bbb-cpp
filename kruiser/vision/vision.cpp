#include "camera.hpp"
#include "vision_server.hpp"

#include <cstdlib>
#include <iostream>

#define TCP_PORT 8000
#define CAMERA_FRAME_WIDTH 600
#define CAMERA_FRAME_HEIGHT 480

using namespace std;

int main(int argc, char* argv[])
{
    
    short port = TCP_PORT;
    
    try {
        
        cout << "enabeling Camera" << endl;
        Camera * camera = new Camera(0, CAMERA_FRAME_WIDTH, CAMERA_FRAME_HEIGHT);
        
        cout << "Initializing TCP Server and waiting for connections on port: " << port << endl;
        boost::asio::io_service io_service;
        VisionServer s(io_service, port, camera);
        io_service.run();
        
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    
    /*
    cout << "Starting EBB Server Example" << endl;
    SocketServer server(54321);
    cout << "Listening for a connection..." << endl;
    server.threadedListen();
    */
    
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