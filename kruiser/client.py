#!/usr/bin/env python
  
import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 8000
BUFFER_SIZE = 256
MESSAGE = '{"cmd":"grabbw"}'

def bytes256(str):
    b  = bytearray(256)
    s = str.encode("utf8")
    for idx, c in enumerate(s):
        b[idx] = c 
        
    return b
    
def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((TCP_IP, TCP_PORT))
    str = bytes256(MESSAGE)
    s.send(str)
    data = s.recv(BUFFER_SIZE)
    s.close()
    
    print "received data:", data
    
    
if __name__ == "__main__":
    main()