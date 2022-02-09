# CV_RIcoh
Package for decoding H264 stream to OpenCV. 

1) sudo apt install -y libavcodec-dev libavformat-dev libavdevice-dev libavfilter-dev.
2) Download and compile https://github.com/ricohapi/libuvc-theta NO NEED TO INSTALL!!.
3) Change lines 6,8,9,10,12 of CMakeLists.txt to reflect the location of the included libuvc files and libraries (libuvc.a) you just created in step 2.
4) Compile similar to package of step 1. 
5) Run in terminal with: "LD_LIBRARY_PATH=<PATH_TO libuvc.a from CMakeLists.txt> ./ricoh_cvview"
