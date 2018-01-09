cmake_minimum_required (VERSION 3.7)
project (Vehicle)

find_package( Boost REQUIRED )
find_package( OpenCV REQUIRED )

set(INCLUDE ../network)
set(SOURCES vehicle.cpp)


include_directories (${INCLUDE})

add_executable(Vehicle ${SOURCES})

target_link_libraries(Vehicle boost_system boost_thread roboticscape ${OpenCV_LIBS} pthread)


