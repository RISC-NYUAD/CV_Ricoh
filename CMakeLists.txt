cmake_minimum_required(VERSION 3.1)
project(ricoh_uvc_opencv)

include_directories(/home/ne34/github_packages/libuvc-theta/include)
link_directories(/home/ne34/github_packages/libuvc-theta/build)

find_package(OpenCV 4 REQUIRED) #For imconvertions and imshow
include_directories(include 
					${OpenCV_INCLUDE_DIRS}
					/usr/include/libavcodec
					/usr/include/libavformat
					/usr/include/libswscale)

#sudo apt install -y libavcodec-dev libavformat-dev libavdevice-dev libavfilter-dev

add_executable(ricoh_cvview src/ricoh_opencv.cpp src/thetauvc.c src/H264Decoder.cpp)
target_compile_options(ricoh_cvview PRIVATE -std=c++11 -x c++)
target_link_libraries(ricoh_cvview PRIVATE -luvc -lpthread -lusb-1.0 ${OpenCV_LIBS} -lavcodec -lavformat -lswscale -lavutil)
