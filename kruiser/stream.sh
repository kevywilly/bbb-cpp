#!/bin/bash
#export LD_LIBRARY_PATH=/usr/lib/mjpg-streamer:$LD_LIBRARY_PATH
/sbin/modprobe uvcvideo
/usr/bin/mjpg_streamer -i "input_uvc.so -r 1280x960" -o "output_http.so -p 8001 -w /usr/local/www" 
# "output_file.so -f pics -d 15000"