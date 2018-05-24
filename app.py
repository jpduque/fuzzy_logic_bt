import json
from time import time,sleep
import pyglet
from flask import Flask, render_template, make_response, redirect, url_for, abort
from bluetoothSync import bt
import os
import threading

class app():

    app = Flask(__name__)

    @app.route('/')
    def hello_world():
        return render_template('index.html', data='test')

    @app.route('/order')
    def shut():
        return render_template('layout.html')

    @app.route('/shutdown')
    def shut2():
        killthread = threading.Thread(target=app.kill)
        killthread.start()
        return render_template('layout.html')

    @app.route('/live-data')
    def live_data():
        # Create a PHP array and echo it as JSON
        temperature = bt.run()
        data = [time() * 1000, temperature]
        response = make_response(json.dumps(data))
        response.content_type = 'application/json'
        if temperature > 40:
            music = pyglet.resource.media('alarm.wav')
            music.delete()
            music.play()
        if temperature > 50:
            return redirect(url_for('shut'))
        return response

    def kill():
        sleep(16)
        os.system('pmset displaysleepnow')
        print('im death')


