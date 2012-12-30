#! /usr/bin/python

import time
import RPi.GPIO as GPIO
import sys
import signal

# North side yellow has changed to pin 27 for new Rev 2 board.
# 6-12-12 www.skpang.co.uk

# North set of traffic light
# Define LED colour and their GPIO pin
RED_NORTH = 17
YEL_NORTH = 27
GRN_NORTH = 22

# East set of traffic light
RED_EAST = 25
YEL_EAST = 8
GRN_EAST = 7

GPIO.setmode(GPIO.BCM)

# Setup GPIO pins
GPIO.setup(RED_NORTH, GPIO.OUT)
GPIO.setup(YEL_NORTH, GPIO.OUT)
GPIO.setup(GRN_NORTH, GPIO.OUT)

GPIO.setup(RED_EAST, GPIO.OUT)
GPIO.setup(YEL_EAST, GPIO.OUT)
GPIO.setup(GRN_EAST, GPIO.OUT)

delay = 1

def cleanup_gpio(signal, frame):
    print
    GPIO.cleanup()
    sys.exit(0)

# Install signal handler to cleanup GPIO when user sends SIGINT
signal.signal(signal.SIGINT, cleanup_gpio)

while True:
    GPIO.output(RED_NORTH, True)    #ALL red
    GPIO.output(RED_EAST, True)
    time.sleep (delay)
    time.sleep (delay)

    GPIO.output(YEL_EAST, True)
    time.sleep (delay)
    GPIO.output(YEL_EAST, False)
    GPIO.output(RED_EAST, False)

    GPIO.output(GRN_EAST, True)     # East green
    time.sleep (delay)
    time.sleep (delay)
    GPIO.output(GRN_EAST, False)

    GPIO.output(YEL_EAST, True)
    time.sleep (delay)
    GPIO.output(YEL_EAST, False)

    GPIO.output(RED_EAST, True)     # All red
    time.sleep (delay)
    time.sleep (delay)

    GPIO.output(YEL_NORTH, True)
    time.sleep (delay)
    GPIO.output(YEL_NORTH, False)
    GPIO.output(RED_NORTH, False)

    GPIO.output(GRN_NORTH, True)    # North green
    time.sleep (delay)
    time.sleep (delay)
    GPIO.output(GRN_NORTH, False)

    GPIO.output(YEL_NORTH, True)
    time.sleep (delay)
    GPIO.output(YEL_NORTH, False)
