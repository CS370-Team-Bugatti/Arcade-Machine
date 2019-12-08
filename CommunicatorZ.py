# Write your code here :-)
from gpiozero import MotionSensor
import threading
import signal
import os
import sys

def wait(p):
    os.kill(p, signal.SIGKILL)

def sense():
    pir = MotionSensor(4)
    if (pir.wait_for_motion()):
        return 1

def main():
    pi = os.getpid()
    timer = threading.Timer(5.0, wait, [pi])

    timer.start()

    myfile = open('result.txt', 'a')
    myfile.truncate(0)
    myfile.write("0")

    result = sense()

    myfile.truncate(0)
    myfile.write("1")

if __name__=="__main__":
    main()