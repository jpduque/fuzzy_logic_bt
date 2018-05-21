import serial
from time import sleep

def run():
    input_data = '';
    port="/dev/tty.HC-05-DevB" #This will be different for various devices and on windows it will probably be a COM port.
    bluetooth=serial.Serial(port, 9600)#Start communications with the bluetooth unit
    bluetooth.flushInput() #This gives the bluetooth a little kick
    bluetooth.write(b"BOOP "+str.encode(str(1)))#These need to be bytes not unicode, plus a number
    sleep(1)
    while bluetooth.in_waiting > 0:
        input_data=bluetooth.readline()#This reads the incoming data. In this particular example it will be the "Hello from Blue" line
    if input_data == '':
        return run()
    print(input_data.decode())#These are bytes coming in so a decode is needed
    sleep(0.1) #A pause between bursts
    temperature = input_data.decode()
    temperature = temperature[:-2]
    bluetooth.close()
    return float(temperature)
