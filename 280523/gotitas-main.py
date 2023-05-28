#Este archivo se ejecuta cuando la RPI hace boot
#esta en la rpi babadeperro

import time
time.sleep(10)
from gtts import gTTS
import markovify
import os
# to be able to use the soundcard
import soundcard as sc
# for reading sound files
import soundfile as sf
import serial
import subprocess

def speak(text):
    tts = gTTS(text=text, lang='es')
    filename = "abc.mp3"
    tts.save(filename)


with open("/home/babadeperro/Documentos/gotitas-con-baba-de-perro/RAW_WhatsAppChatwithNuriaNia2.txt") as f:
    text_a = f.read()
with open("/home/babadeperro/Documentos/gotitas-con-baba-de-perro/textos_libros_limpios.txt") as g:
    text_b = g.read()

model_nutria = markovify.Text(text_a)
model_remedios = markovify.Text(text_b)
model_combo = markovify.combine([ model_nutria, model_remedios ], [ 0.5, 1.5 ])

# voice 
#Configure the SoundCard
# print all speackers if necessary to select the soundcard
speakers = sc.all_speakers()
print(speakers)
# define the default speacker
default_speaker = sc.default_speaker()
# select the right speacker
#sc.get_speaker('Scarlett')
sc.get_speaker('Komplete Audio 6')
#sc.get_speaker('Speaker Built-in Audio Analog Stereo (2 channels)')




if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
           #print(line)
            if line =='1':
                print("MURMULLO")
                from unidecode import unidecode
                # create a sentence
                string = model_combo.make_sentence()
                # eliminate the accents and spetial characters
                #string = unidecode(string)
                string = string.replace(',', '')
                string = string.replace('?', '')
                string = string.replace('!', '')
                print(string)
                #if os.path.isfile("./voz.mp3"):
                #    print('siii')
                #    os.remove("./voz.mp3")
                speak(string)
                import subprocess
                #if os.path.isfile("./voz.wav"):
                #    os.remove("./voz.wav")
                subprocess.call(["ffmpeg", "-y", "-i", "abc.mp3", "abc.wav"])
                print("subprocess finished")
                #read wav files using soundfile
                data3, samplerate2 = sf.read('./abc.wav')
                #maps the data into the interface channels
                #default_speaker.play(data=data3, channels=[1],samplerate=22050)
                default_speaker.play(data=data3, channels=[0],samplerate=25000)
                time.sleep(11)
                ser.reset_input_buffer()
            if line == '3':
                print("SHUTTING DOWN")
                subprocess.run(["sudo", "shutdown", "-h", "now"])
