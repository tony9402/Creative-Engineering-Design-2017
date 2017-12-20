#!/usr/bin/env python

import os
import serial
import time
import random

list = ['0','1','2']

portcount = 0
port = ["/dev/ttyUSB","/dev/ttyACM"]
portListCheck = 0
omxplayerMusic = 'omxplayer -o local ~/Desktop/AED/'

while(os.system('ls /dev/ttyUSB'+list[portcount]) != 0):
    portcount = portcount + 1
    if(portcount >= 3):
        portListCheck = 1
        portcount = 0
        break
omxplayMusic = 'omxplayer -o local ~/Desktop/AED/'
while(os.system('ls /dev/ttyACM'+list[portcount]) != 0):
    portcount = portcount + 1
    if(portcount >= 3):
        break
serialFromArduino = serial.Serial(port[portListCheck]+list[portcount],9600);
serialFromArduino.flushInput()
MusicNum = 0
musicrand = 0

while True:
    input_s = serialFromArduino.readline()
    input = int(input_s)
    print(input)
    if(input >= 40 and input <= 155):
        if(input >= 150):
            MusicNum = 155
            musicrand = int(random.random()) % 2 + 1
            os.system(omxplayerMusic + str(MusicNum)+'_'+str(musicrand)+'.mp3')
        elif(input >= 140):
            MusicNum = 145
            musicrand = int(random.random()) % 2 + 1
            os.system(omxplayerMusic + str(MusicNum)+'_'+str(musicrand)+'.mp3')
        elif(input >= 130):
            MusicNum = 135
            os.system(omxplayerMusic + str(MusicNum)+'_1.mp3')
        elif(input >= 110):
            MusicNum = 125
            os.system(omxplayerMusic + str(MusicNum)+'_1.mp3')
        elif(input >= 100):
            MusicNum = 105
            os.system(omxplayerMusic + str(MusicNum)+'_1.mp3')
        elif(input >= 90):
            MusicNum = 95
            musicrand = int(random.random()) % 2 + 1
            os.system(omxplayerMusic + str(MusicNum)+'_'+str(musicrand)+'.mp3')
        elif(input>=80):
            MusicNum = 85
            musicrand = int(random.random()) % 2 + 1
            os.system(omxplayerMusic + str(MusicNum)+'_'+str(musicrand)+'.mp3')
        elif(input>=70):
            MusicNum = 75
            musicrand = int(random.random()) % 2 + 1
            os.system(omxplayerMusic + str(MusicNum)+'_'+str(musicrand)+'.mp3')
        elif(input>=60):
            MusicNum = 65
            musicrand = int(random.random()) % 2 + 1
            os.system(omxplayerMusic + str(MusicNum)+'_'+str(musicrand)+'.mp3')
        elif(input>=50):
            MusicNum = 55
            musicrand = int(random.random()) % 2 + 1
            os.system(omxplayerMusic + str(MusicNum)+'_'+str(musicrand)+'.mp3')
        elif(input>=40):
            MusicNum = 45
            os.system(omxplayerMusic + str(MusicNum)+'_1.mp3')
        else:
            print("ERROR BPM")
