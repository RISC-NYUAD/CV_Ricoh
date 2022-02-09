/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (C) 2010-2012 Ken Tossell
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the author nor other contributors may be
 *     used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/
//System
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <iostream>

//OpenCV
#include <opencv2/opencv.hpp>

//libuvc-theta
#include "libuvc/libuvc.h"
#include "thetauvc.h"
const int THETA_MODE = THETAUVC_MODE_FHD_2997;

//H264 decoder
#include "H264Decoder.h"
unsigned char buf[700000];//should be max enough
H264Decoder decoder;

void cb(uvc_frame_t *frame, void* usr_data_) {
	decoder.decode((unsigned char*) frame->data, frame->data_bytes);
	decoder.play();
}

int main(int argc, char **argv) {
	uvc_context_t *ctx;
	uvc_error_t res;
	uvc_device_t *dev;
	uvc_device_handle_t *devh;
	
	res = uvc_init(&ctx, NULL);
	if (res != UVC_SUCCESS) {
		std::cout << "UVC not initialized" << std::endl;
		return res;
	}
	else std::cout << "UVC initialized" << std::endl;
	
	res = thetauvc_find_device(ctx, &dev, 0);
	if (res != UVC_SUCCESS) {
		std::cout << "THETA not found" << std::endl;
		return -1;
	}
	else std::cout << "THETA found" << std::endl;
	
	int usr_data = 0;
	res = thetauvc_run_streaming(dev, &devh, THETAUVC_MODE_FHD_2997, cb, (void*) &usr_data);
	decoder.init();
 	while(1){//Main loop 
		
	}
	uvc_stop_streaming(devh);
	printf("\nDevice closed %d \n",(int) res);
	uvc_unref_device(dev);
	uvc_exit(ctx);
	return 0;
}

