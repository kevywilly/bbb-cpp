#!/bin/bash
export LD_LIBRARY_PATH=/usr/lib/mjpg-streamer:$LD_LIBRARY_PATH
/usr/bin/mjpg_streamer -i "input_uvc.so" -o "output_http.so -p 8090 -w /usr/local/www" 
