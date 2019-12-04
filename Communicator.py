# Write your code here :-)
from gpiozero import MotionSensor

def sense():
    pir = MotionSensor(4)
    if (pir.wait_for_motion()):
        return 1
    
sense()
