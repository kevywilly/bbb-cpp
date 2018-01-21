#!/usr/bin/python

import urllib
import cv2
import numpy as np

URL = "http://192.168.1.83:8001?action=snapshot"
BLUR = (10,10)

def grabImage():
    global URL
    response = urllib.urlopen(URL)
    imgArray = np.array(bytearray(response.read()), dtype = np.uint8)
    img = cv2.imdecode(imgArray,cv2.IMREAD_GRAYSCALE)
    cv2.imwrite('images/img.png',img)
    blur = cv2.blur(img,BLUR)
    edges = cv2.Canny(blur,10,30,3)
    cv2.imwrite('images/edges.png',edges)
    
def main():
    grabImage()
    
    
if __name__ == "__main__":
    main()