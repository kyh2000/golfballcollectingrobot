import serial
import threading
import time
import RPi.GPIO as GPIO
import cv2
import numpy as np
import time
import sys
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
camerabool=True
checking=0
TRIG=3
ECHO=4
cap = cv2.VideoCapture(0)
gocontrol = True
i = 0
counter=1
ultracounter=0
colordetect=0
colorcounter=0
width = 0
prev_time = 0
height = 0
color = 0 # average color of image
FPS = 10
GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)

py_serial = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=9600, timeout=1
)
def check_img_info():
    while(True):
        ret, img = cap.read()
        if ret:
            print("*"*50)
            x = img.shape[1]
            y = img.shape[0]
            print('Width:', x, ' Height:', y)
            print("*"*50)
            break
    return x, y
 
def check_color_pattern(frame):
    global colorcounter, hue,camerabool,val,val1,result
    hls = cv2.cvtColor(frame, cv2.COLOR_BGR2HLS)
    counter = 1
    sum_hue = 0
    for i in range(50, width-50, 20):
        for j in range(50, height-50, 20):
            sum_hue = sum_hue + (hls[j, i, 0]*2)
            counter = counter + 1
             
    hue = sum_hue/counter
    if (camerabool==True):

        print('Average Hue: ', hue)
       
        if( 0 <= hue <= 80):
            if(checking>80):
                
                gocontrol=False
                colordetect=1
                colorcounter+=1
                if colordetect==1:
                    print("color check")
                    if colorcounter==9:
                        colorcounter=1
                        
                       
                    if colorcounter == 1:
                            camerabool=False
                            leftturn()
                            print("turn left")
                            time.sleep(13)
                    if colorcounter == 3:
                            camerabool=False
                            rightturn()
                            print("turn right")
                            time.sleep(13)
            
                    if colorcounter == 7:
                            camerabool=False
                            #leftturn()
                            print("finish")
                            #time.sleep(13)
                            finish()
                            time.sleep(10000)
                    if colorcounter == 5:
                            camerabool=False
                            rightturn()
                            print("turn right")
                            time.sleep(13)
               
                    if colorcounter%2==0:
                        print("ignore")
                        camerabool=False
                        time.sleep(1)
                    #time.sleep(3)
                    #rightUturn()
                    #time.sleep(7)
                colordetect=0
            gocontrol=True
            camerabool=True
def webcam():
    global prev_time,counter
    ret, frame = cap.read()
    #cv2.imshow("test", frame)
    frame_s = cv2.resize(frame, None, fx = 0.2, fy = 0.2, interpolation = cv2.INTER_AREA)
    current_time = time.time() - prev_time

    if (ret is True) and (current_time > 1./ FPS) :
        prev_time = time.time()
    if ret:
  #      cv2.imshow('Video', frame_s)
        counter = counter + 1
        px = frame[100, 100] # [y, x] 순서 주의
        hls = cv2.cvtColor(frame, cv2.COLOR_BGR2HLS)
        color = check_color_pattern(frame)
def meas():
    global distance, checking
    GPIO.output(TRIG,False)
 #   GPIO.output(TRIG1,False)
    time.sleep(0.1)
    GPIO.output(TRIG,True)
    time.sleep(0.00001)       
    GPIO.output(TRIG, False)
        
    while GPIO.input(ECHO)==0:
        start = time.time()     
            
    while GPIO.input(ECHO)==1:
        stop = time.time()      
            
    check_time = stop - start
    distance = check_time * 34300 / 2
    print("Distance : %.1f cm" % distance)
    time.sleep(0.1)
    checking = hue
    print(checking)    
   

def gofoward():
    while True:
        if(gocontrol == True):
            py_serial.write(go.encode())
            
            time.sleep(0.1)
            
            if py_serial.readable():
                
                response = py_serial.readline()
                print(response[:len(response)-1].decode())
def rightturn():
    py_serial.write(right.encode())
    
    time.sleep(0.1)
    
    if py_serial.readable():
        
        response = py_serial.readline()
        print(response[:len(response)-1].decode())
        
def leftturn():
    py_serial.write(left.encode())
    
    time.sleep(0.1)
    
    if py_serial.readable():
        
        response = py_serial.readline()
        print(response[:len(response)-1].decode())
        
def rightUturn():
    py_serial.write(rut.encode())
    
    time.sleep(0.1)
    
    if py_serial.readable():
        
        response = py_serial.readline()
        print(response[:len(response)-1].decode())
        
def leftUturn():
    py_serial.write(lut.encode())
    
    time.sleep(0.1)
    
    if py_serial.readable():
        
        response = py_serial.readline()
        print(response[:len(response)-1].decode())
def sound():
    py_serial.write(sud.encode())
    
    time.sleep(0.1)
    
    if py_serial.readable():
        
        response = py_serial.readline()
        print(response[:len(response)-1].decode())
def start():
    py_serial.write(srt.encode())
    
    time.sleep(0.1)
    
    if py_serial.readable():
        
        response = py_serial.readline()
        print(response[:len(response)-1].decode())
def finish():
    py_serial.write(fin.encode())
    
    time.sleep(0.1)
    
    if py_serial.readable():
        
        response = py_serial.readline()
        print(response[:len(response)-1].decode())

width, height = check_img_info()
print('width: ', width, 'height: ', height)
if __name__ == "__main__": #main function
    go = 'g'
    right = 'd'
    left = 'a'
    rut = 'r'
    lut = 'l'
    sud = 's'
    fin = 'f'    
    srt = 't'
    start()
    width, height = check_img_info()
    print('width: ', width, 'height: ', height)
    t3= threading.Thread(target=gofoward)
    #t4= threading.Thread(target=weight)
    t3.start()
    #t4.start()
    while(True):
        
        webcam()
        meas()
        while distance<30:
            gocontrol=False
            sound()
            time.sleep(5)
            meas()
            if distance>30:
                gocontrol=True
                break
