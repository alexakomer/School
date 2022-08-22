import RPi.GPIO as GPIO
from time import sleep

#A: 19, B: 16, C: 12, D: 6, E: 13, F: 20, G:21
sevseg_io = [19,16,12,6,13,20,21] #GPIO ports used for seven segment display
rgb1_io = [22,27,17]
rgb2_io = [25,24,23]
button_io = 18
numbers = [[19,16,12,6,13,20],
           [16,12],
           [19,16,6,13,21],
           [19,16,12,6,21],
           [16,12,20,21],
           [19,12,6,20,21],
           [19,12,6,13,20,21],
           [19,16,12],
           [19,16,12,6,13,20,21],
           [19,16,12,6,20,21]]

def init():
    setup_GPIO()
    reset()
    GPIO.output(rgb2_io[1], 1)
    GPIO.output(rgb1_io[0], 1)

def reset():
    flush_display()
    flush_led()

def flush_led():
    GPIO.output(rgb1_io, 0)
    GPIO.output(rgb2_io, 0)

def flush_display():
    GPIO.output(sevseg_io, 0)

def setup_GPIO():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(button_io, GPIO.IN)
    GPIO.setup(rgb1_io, GPIO.OUT)
    GPIO.setup(rgb2_io, GPIO.OUT)
    GPIO.setup(sevseg_io, GPIO.OUT)
    
def change_color(rgb, r, g, b):
    GPIO.output(rgb, 0)
    GPIO.output(rgb[0], r)
    GPIO.output(rgb[1], g)
    GPIO.output(rgb[2], b)
    
def blink():
    for i in range(0,3):
        GPIO.output(rgb2_io[2], 1)
        sleep(0.5)
        GPIO.output(rgb2_io[2], 0)
        sleep(0.5)
    change_color(rgb2_io, 1, 0, 0)
    
def countdown():
    for i in range(9,-1,-1):
        GPIO.output(numbers[i], 1)
        if i <= 4 and i%2 == 0:
            change_color(rgb1_io, 0, 0, 1)
        elif i <= 4 and i%2 != 0:
            change_color(rgb1_io, 0, 0, 0)

        sleep(1)
        GPIO.output(numbers[i], 0)
        
def logic(pin):
    GPIO.output(rgb2_io[1], 0)
    GPIO.output(rgb2_io[2], 1)
    blink()
    change_color(rgb1_io, 0, 1, 0)
    countdown()
    change_color(rgb1_io, 1, 0, 0)
    change_color(rgb2_io, 0, 1, 0)
    sleep(10)
    

def polling_method():
    init()
    
    while True:
        if not GPIO.input(button_io):
            logic(0)
        

def interrupt_method():
    init()
    GPIO.add_event_detect(button_io, GPIO.RISING, logic)

interrupt_method()
