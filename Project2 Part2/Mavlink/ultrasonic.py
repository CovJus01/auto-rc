import RPi.GPIO as GPIO
import time

GPIO_TRIGGER = 23
GPIO_ECHO = 24

def ultrasonic_setup():
    GPIO.setmode(GPIO.BCM)
    
    GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
    GPIO.setup(GPIO_ECHO, GPIO.IN)
    
    
def distance():
    
    GPIO.output(GPIO_TRIGGER, True)
    
    time.sleep(0.00001)
    GPIO.output(GPIO_TRIGGER, False)
    
    StartTime = time.time()
    StopTime = time.time()
    
    while GPIO.input(GPIO_ECHO) == 0:
        StartTime = time.time()
        
    while GPIO.input(GPIO_ECHO) ==1:
        StopTime = time.time()
        
    TimeElapsed = StopTime - StartTime
    
    distance = (TimeElapsed * 34300) /2
    
    return distance



if __name__ == "__main__":
    GPIO_TRIGGER = 23
    GPIO_ECHO = 24
    ultrasonic_setup();
    while True:
        dist = distance()
        print("Measured Distance = %.1f cm" % dist)
        time.sleep(0.1)
    
