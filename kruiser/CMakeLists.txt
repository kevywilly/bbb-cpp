cmake_minimum_required (VERSION 3.7)
project (Kruiser)

find_package( Boost REQUIRED )
#find_package( OpenCV REQUIRED )

set(INCLUDE json network robotcape vehicle)
set(SOURCES kruiser.cpp)


include_directories (${INCLUDE})

add_executable(Kruiser ${SOURCES})

#target_link_libraries(Kruiser boost_system boost_thread roboticscape ${OpenCV_LIBS} pthread)
target_link_libraries(Kruiser boost_system boost_thread roboticscape pthread)

install(TARGETS Kruiser DESTINATION /usr/bin)
