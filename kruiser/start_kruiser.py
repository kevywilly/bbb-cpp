#!/usr/bin/python
from threading import Thread 
import subprocess


def start_streamer():
    subprocess.call(["/usr/bin/mjpg_streamer","-i","input_uvc.so","-o","output_http.so -p 8001 -w /usr/local/www"  ])

def start_vehicle():
    subprocess.call(["/usr/bin/Kruiser","8000"])


def main():
    t1 = Thread(target = start_streamer)
    t2 = Thread(target = start_vehicle)
    
    t1.start()
    t2.start()
    
    
if __name__ == "__main__":
    main()
