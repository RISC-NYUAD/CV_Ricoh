cmake_minimum_required(VERSION 3.1)
project(ricoh_uvc_opencv)

find_package(OpenCV 4 REQUIRED) #For imconvertions and imshow
include_directories(include 
					/home/ne34/github_packages/libuvc-theta/include
					${OpenCV_INCLUDE_DIRS}
					/usr/include/libavcodec
					/usr/include/libavformat
					/usr/include/libswscale)
					
link_directories(/home/ne34/github_packages/libuvc-theta/build)

#sudo apt install -y libavcodec-dev libavformat-dev libavdevice-dev libavfilter-dev

add_executable(ricoh_cvview src/ricoh_opencv.cpp src/thetauvc.c src/H264Decoder.cpp)
target_compile_options(ricoh_cvview PRIVATE -std=c++11 -x c++)
target_link_libraries(ricoh_cvview PRIVATE -luvc ${OpenCV_LIBS} -lavcodec -lavformat -lswscale -lavutil)
