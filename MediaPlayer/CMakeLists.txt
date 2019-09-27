cmake_minimum_required(VERSION 3.7)

SET(CMAKE_CXX_STANDARD 11)

set(CROSS_COMPILING_ROOT /opt/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf)
set(CMAKE_C_COMPILER /opt/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER /opt/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)

set(SOURCE_FILE
    src/MediaPlayerVlc.cpp
    src/test.cpp
	)

include_directories(include)
link_directories("lib")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

ADD_EXECUTABLE(mediaPlayer ${SOURCE_FILE})
target_link_libraries(mediaPlayer -lstdc++ -Llib -lvlc)
