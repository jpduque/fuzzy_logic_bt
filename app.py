import json
from time import time
import serial
from flask import Flask, render_template, make_response
import bluetoothSync

app = Flask(__name__)

port="/dev/tty.HC-05-DevB" #This will be different for various devices and on windows it will probably be a COM port.
bluetooth=serial.Serial(port, 9600)#Start communications with the bluetooth unit
bluetooth.flushInput() #This gives the bluetooth a little kick


@app.route('/')
def hello_world():
    return render_template('index.html', data='test')

@app.route('/live-data')
def live_data():
    # Create a PHP array and echo it as JSON
    data = [time() * 1000, bluetoothSync.run(bluetooth)]
    response = make_response(json.dumps(data))
    response.content_type = 'application/json'
    return response

if __name__ == '__main__':
    app.run(debug=True, host='127.0.0.1', port=5000)
