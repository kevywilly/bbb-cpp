#include "../robotcape/robotcape.hpp"
#include "../network/server.hpp"
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
void callback(char * payload) {
	if(string(payload) != previous_payload) {
		previous_payload = string(payload);
		// drivetrain.drive()
		cout << payload << endl;
	}
}


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
		
	    
	    drivetrain.drive(0.25, 45.0);
	    io_service.run();
	    
	  }
	  catch (std::exception& e)
	  {
	    std::cerr << "Exception: " << e.what() << "\n";
	  }

 
	cleanup();
	return 0;
   
}