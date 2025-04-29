import cv2
import numpy as np
import math
import RPi.GPIO as GPIO
import time
from pymavlink import mavutil
import camera as cam
import ultrasonic as ultra


if __name__ == "__main__":


    conn = mavutil.mavlink_connection('/dev/ttyACM0')
    conn.wait_heartbeat()
    print("Heartbeat from system (system %u component %u" % (conn.target_system, conn.target_component))

    ultra.ultrasonic_setup();

    
    while(1):
        cam_ret = cam.process_camera_frame() # 0 L, 1 F, 2 R
        distance = ultra.distance()
        #print(f"Camera value: {cam_ret}\nUltra value : {distance}")
        message = mavutil.mavlink.MAVLink_debug_message(0, cam_ret, distance)
        conn.mav.send(message)
        print("Value Sent")
        time.sleep(0.4)
        debug_msg = conn.recv_match(type = 'DEBUG', blocking = True)

        
    
    


        

        
