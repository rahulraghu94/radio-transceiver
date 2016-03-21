#!/usr/bin/python
# -*- coding: utf-8 -*-

from nrf24 import NRF24
import time


#Hex pipes on BBB
pipes = [[0xe7, 0xe7, 0xe7, 0xe7, 0xe7], [0xc2, 0xc2, 0xc2, 0xc2, 0xc2]]

#Creating instance of the radio
radio = NRF24()

#Start radio
radio.begin(1, 0, "P8_23", "P8_24")

#Set the number and delay of retries upon failed submit.
radio.setRetries(15,15)

#Sets a static payoad size.
#radio.setPayloadSize(8)

radio.setPALevel(NRF24.PA_LOW)

#This will respond to all incoming messages
#How ever, teh transmitter will only check ever 100 sent packets for ack
#Transmitter will not even be listening the rest of the time
radio.setAutoAck(1)

#Channels for reading: Accepting packets
#Channel for writing: Sendin ACKs
radio.openWritingPipe(pipes[0])
radio.openReadingPipe(1, pipes[1])

#Kinda like a caliberation
radio.startListening()
radio.stopListening()

#Enable if you wish details of the radio.
#For debugging only
radio.printDetails()

#start listening for data
radio.startListening()

while True:
    pipe = [0]
    while not radio.available(pipe, True):
        time.sleep(1000/1000000.0)

    recv_buffer = []
    radio.read(recv_buffer);
    print recv_buffer
