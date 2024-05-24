import cv2
import serial
import time
import numpy as np
from math import atan2, degrees

# Open serial connection to Arduino
arduino = serial.Serial('COM12', 9600)

def detect_sun_position(frame):
    # Convert the image to grayscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Blur the image to reduce noise
    blurred = cv2.GaussianBlur(gray, (11, 11), 0)

    # Apply thresholding to isolate the brightest spots
    _, thresholded = cv2.threshold(blurred, 200, 255, cv2.THRESH_BINARY)

    # Find contours in the thresholded image
    contours, _ = cv2.findContours(thresholded.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # If no contours were found, return None
    if not contours:
        return None

    # Otherwise, find the largest contour (assumed to be the sun)
    max_contour = max(contours, key=cv2.contourArea)

    # Calculate the center of the contour
    M = cv2.moments(max_contour)
    cX = int(M["m10"] / M["m00"])
    cY = int(M["m01"] / M["m00"])

    return cX, cY
# Function to map values
def map_value(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

# Function to convert pixel coordinates to azimuth and elevation
def pixel_to_azimuth_elevation(x, y, image_width, image_height):
    # Calibration parameters (adjust as needed)
    fov_horizontal = 70  # Horizontal field of view in degrees
    fov_vertical = 50    # Vertical field of view in degrees

    # Calculate azimuth and elevation based on pixel coordinates
    azimuth = map_value(x, 0, image_width, -fov_horizontal / 2, fov_horizontal / 2)
    elevation = map_value(y, 0, image_height, -fov_vertical / 2, fov_vertical / 2)

    return azimuth, elevation

# Open the default camera
cap = cv2.VideoCapture(0)

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Find sun position
    sun_x, sun_y = detect_sun_position(frame)

    # Convert coordinates to azimuth and elevation
    image_height, image_width, _ = frame.shape
    azimuth, elevation = pixel_to_azimuth_elevation(sun_x, sun_y, image_width, image_height)

    # Map elevation to range 0-180
    elevation = map_value(elevation, -90, 90, 0, 180)

    # Send azimuth and elevation data to Arduino
    data_to_send = f"{azimuth:.2f},{elevation:.2f}\n"
    arduino.write(data_to_send.encode())

    # Wait for 5 seconds
    time.sleep(5)

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()