
#include "robotcape/robotcape.hpp"
#include "network/server.hpp"
#include "json/json_payload.hpp"
#include "vehicle/drivetrain.hpp"
#include "vehicle/camera_mount.hpp"
//#include "camera.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

using namespace std;

#define CAMERA_FRAME_WIDTH 1200
#define CAMERA_FRAME_HEIGHT 960

// Drivetrain
Drivetrain drivetrain(1,2);
// Camera Mount
CameraMount camera_mount(1,2);

// Track payloads
string previous_payload = "";

// Set camera ptr
boost::thread * camera_mount_ptr;

/********************
 * Cleanup
 ********************/

void cleanup() {
	try {
	if(rc_get_state() == RUNNING)
		// cleanup drivetrain
		drivetrain.free_spin();
		drivetrain.disable();
		// cleanup camera mount
		camera_mount.free_spin();
		camera_mount.disable();
		camera_mount_ptr->interrupt();
		
		
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


/*********************************
 * Callback from TCP Server
 *********************************/
void callback(const string& payload) {
	
	string tmp_payload = previous_payload;
	previous_payload = payload;
	
	JsonPayload json(payload);
	
	std::string cmd = json.getStringOr("cmd","None");
	
	cout << "Got Callback" << endl;
	
	if(cmd == "drive" && payload != tmp_payload) 
	{
				// Change drive parameters
				float speed = json.getFloatOr("speed",0.0);
				float turn = json.getFloatOr("turn",0.0);
			  cout << "cmd:" << cmd << "speed: " << speed << "turn:" << turn << endl;
			  drivetrain.drive(speed, turn);
	} 
		else if(cmd == "look" && payload != tmp_payload) 
	{
				// Adjust camera mount
				float yaw = json.getFloatOr("yaw",0.0);
				float pitch = json.getFloatOr("pitch",0.0);
			  cout << "cmd: " << cmd << "yaw: " << yaw << "pitch: " << pitch << endl;
			  camera_mount.look(yaw, pitch);
	} 


}

void wait(int millis)
{
  boost::this_thread::sleep_for(boost::chrono::milliseconds{millis});
}

// Thread to send pulses ever 20 ms
void camera_mount_thread()
{
  while(true)
  {
    wait(20);
    camera_mount.send_pulses();
  }
}
/********************
 * Main Entry Point
 *******************/

int main(int argc, char* argv[])
{
	
	try{
		
				// Check Args
			  if (argc != 2){
		      std::cerr << "Usage: Vehicle <port>\n";
		      return 1;
		    }
		    
		    // Get Port Assignment
		    int port = atoi(argv[1]);
		    
				// Enable Roboticscape
				cout << "Enabeling Roboticscape" << endl;
				if(rc_initialize()){
					cout << "ERROR: failed to initialize rc_initialize(), are you root?\n" << endl;
					return -1;
				}
		
			
				// Disable Drivetrain
				drivetrain.disable();
				
				// Initialize Camera Mount
				camera_mount.enable();
				boost::thread t{camera_mount_thread};
				camera_mount_ptr = &t;
				
				// create service
			  boost::asio::io_service io_service;
			    
			  // handler for service interrupt
				boost::asio::signal_set signals(io_service, SIGINT, SIGTERM );
				server s(io_service, port, callback);
				signals.async_wait( handler );
				
				//run TCP service
				cout << "Starting Vehicle Server listening on "<< port << endl;
				cout << "Press Ctrl-C to exit "<< endl;
				io_service.run();
	    
			}
	  		catch (std::exception& e)
	  	{
	    	std::cerr << "Exception: " << e.what() << "\n";
	  	}

 
	cleanup();
	return 0;
   
}


