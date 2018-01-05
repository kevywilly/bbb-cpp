echo "Building Kruiser for Beaglebone Blue"
g++ -O2 `pkg-config --cflags --libs opencv` kruiser.cpp camera/Camera.cpp network/SocketServer.cpp -o kruiser
