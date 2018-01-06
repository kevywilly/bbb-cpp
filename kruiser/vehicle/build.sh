#make
#gcc -shared -o librobotcape.so robotcape.so
#export LD_LIBRARY_PATH=/usr/lib:$LD_LIBRARY_PATH
g++ -Wall -L /usr/lib -o vehicle vehicle.cpp -lroboticscape -lpthread -lboost_system
