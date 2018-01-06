#include "../robotcape/robotcape.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if(rc_initialize()){
		cout << "ERROR: failed to initialize rc_initialize(), are you root?\n" << endl;
		return -1;
	}

	rc_cleanup(); 
	return 0;
   
}