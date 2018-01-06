cmake_minimum_required (VERSION 3.7)
project (Vehicle)

set(INCLUDE ../network)
set(SOURCES vehicle.cpp)


include_directories (${INCLUDE})

add_executable(Vehicle ${SOURCES})

target_link_libraries(Vehicle boost_system roboticscape pthread)


