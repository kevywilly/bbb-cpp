#include "../robotcape/robotcape.hpp"
#include "../network/server.hpp"
#include "../json/json_payload.hpp"
#include "drivetrain.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;


// Drivetrain
Drivetrain drivetrain(1,2);

// Track payloads
string previous_payload = "";

/********************
 * Cleanup
 ********************/

void cleanup() {
	try {
	if(rc_get_state() == RUNNING)
		drivetrain.free_spin();
		drivetrain.disable();
		
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
	
	if(payload == previous_payload) 
		return;
	previous_payload = payload;
	
	JsonPayload json(payload);
	
	std::string cmd = json.getStringOr("cmd","None");
	float speed = json.getFloatOr("speed",0.0);
	float angle = json.getFloatOr("angle",0.0);
	
	cout << "Got Callback" << endl;
	cout << "cmd:" << cmd << "speed: " << speed << endl;
	
	drivetrain.drive(speed, angle);
}

/*
int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    server(io_service, std::atoi(argv[1]), callback);
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}*/
/********************
 * Main Entry Point
 *******************/

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
		cout << "Starting Vehicle Server listening on "<< port << endl;
		cout << "Press Ctrl-C to exit "<< endl;
		
	    
	    drivetrain.disable();
	    io_service.run();
	    
	  }
	  catch (std::exception& e)
	  {
	    std::cerr << "Exception: " << e.what() << "\n";
	  }

 
	cleanup();
	return 0;
   
}