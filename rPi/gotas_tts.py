#!bin/bash -i
import time
import markovify
import soundcard as sc
import soundfile as sf
import subprocess
from random import randrange

#serial
import serial

def texttowav(text,filename):
    subprocess.call(["espeak", "-s140", "-ves+f4", "-w"+filename+".wav", text])

with open("/home/tresymedio/Desktop/gotitas-con-baba-de-perro/RAW_WhatsAppChatwithNuriaNia2.txt") as f:
    text_a = f.read()
with open("/home/tresymedio/Desktop/gotitas-con-baba-de-perro/textos_libros_limpios.txt") as g:
    text_b = g.read()

model_nutria = markovify.Text(text_a)
model_remedios = markovify.Text(text_b)
model_combo = markovify.combine([ model_nutria, model_remedios ], [ 0.5, 1.5 ])
#murmullo = model_combo.make_sentence()
#texttowav(murmullo,"gotita")

speakers = sc.all_speakers()
default_speaker = sc.default_speaker()
#default_speaker.channels = 2
left_speaker = sc.get_speaker(speakers[0].name)


if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            if line  == '1':
                print("MURMULLO")
                murmullo = model_combo.make_sentence()
                texttowav(murmullo,"gotita") 
                data, samplerate = sf.read("gotita.wav")
                #r = randrange(2)
                #left_speaker.play(data=data,samplerate=22050,channels=[r])
                left_speaker.play(data=data,samplerate = 19000,channels=[0])
                time.sleep(5)
