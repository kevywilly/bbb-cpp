#include "camera.hpp"
#include "../robotcape/robotcape.hpp"
#include "../network/server.hpp"
#include "../json/json_payload.hpp"

#include <cstdlib>
#include <iostream>

#define TCP_PORT 8001
#define CAMERA_FRAME_WIDTH 600
#define CAMERA_FRAME_HEIGHT 480

using namespace std;

// setup camera
Camera camera(0, CAMERA_FRAME_WIDTH, CAMERA_FRAME_HEIGHT);

/********************
 * Cleanup
 ********************/

void cleanup() {
	try {
	rc_cleanup();
	} catch (std::exception& e) {
	    std::cerr << "Exception: " << e.what() << "\n";
	}
}

/********************
 * Ctrl-C Handler
 ********************/
void handler( const boost::system::error_code& error , int signal_number )
{
  std::cout << "handling signal " << signal_number << std::endl;
  cleanup();
  exit(1);
}


/********************
 * Callback
 *******************/
void callback(const string& payload) {
	
	JsonPayload json(payload);
	cout << "received command: " << payload << endl;
	
	std::string cmd = json.getStringOr("cmd","None");
	
	cout << "cmd: " << cmd << endl;
	
	if(cmd == "grabbw") {
	    camera.grab_bw();
	}
}

int main(int argc, char* argv[])
{
    
   	// Enabeling Roboticscape
	cout << "Enabeling Roboticscape" << endl;
	if(rc_initialize()){
		cout << "ERROR: failed to initialize rc_initialize(), are you root?\n" << endl;
		return -1;
	}
	
	try{
	    if (argc != 2){
	      std::cerr << "Usage: async_tcp_echo_server <port>\n";
	      return 1;
	    }
	
		int port = atoi(argv[1]);
		
		// create service
	    boost::asio::io_service io_service;
	    
	    // handler for service interrupt
		boost::asio::signal_set signals(io_service, SIGINT );
		server s(io_service, port, callback);
		
		signals.async_wait( handler );
	  
		//run service
		cout << "Starting Vision Server listening on "<< port << endl;
		cout << "Press Ctrl-C to exit "<< endl;
		
	    io_service.run();
	    
	  }
	  catch (std::exception& e)
	  {
	    std::cerr << "Exception: " << e.what() << "\n";
	  }

 
	cleanup();
	return 0;
    
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