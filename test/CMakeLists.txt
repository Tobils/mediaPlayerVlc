set(CROSS_COMPILING_ROOT /opt/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf)
set(CMAKE_C_COMPILER /opt/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER /opt/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)

SET(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN/lib'" )

add_executable(MediaPlayerTest test.cpp)

target_include_directories(MediaPlayerTest PUBLIC
    "${MediaPlayerVlc_SOURCE_DIR}/include"
)

target_link_libraries(MediaPlayerTest
    MediaPlayerVLC
)