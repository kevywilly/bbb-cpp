#echo "Building Kruiser for Beaglebone Blue"
#g++ -O2 `pkg-config --cflags --libs opencv` kruiser.cpp camera/Camera.cpp network/SocketServer.cpp network/ConnectionHandler.cpp -o kruiser -pthread

#echo "Building Vision System"
#

#echo "Building Kruiser"
g++ -Wall -lroboticscape -lpthread kruiser.cpp -o kruiser
