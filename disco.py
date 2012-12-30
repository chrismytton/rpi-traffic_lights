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

def cleanup_gpio(signal, frame):
    print
    GPIO.cleanup()
    sys.exit(0)

# Install signal handler to cleanup GPIO when user sends SIGINT
signal.signal(signal.SIGINT, cleanup_gpio)

def flash(pin):
    GPIO.output(pin, True)
    time.sleep(0.1)
    GPIO.output(pin, False)

while True:
    flash(RED_NORTH)
    flash(YEL_NORTH)
    flash(GRN_NORTH)
    flash(RED_EAST)
    flash(YEL_EAST)
    flash(GRN_EAST)
