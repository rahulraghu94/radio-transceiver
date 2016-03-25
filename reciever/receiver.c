#include <cstdlib>
#include <iostream>

#include "RF24.h"

/*
  Set CE and CS pins. A hardware configuration.
  Make sure the pin numbers and the function arduments match.
*/
RF24 radio(115, 117);

/* Seting internal pipe adressess.
 */
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup()
{
        printf("Receiver: \n");
        radio.begin();

        /* Set retries takes two arduments.
           The first argument defines the time, in micro
           seconds, after which we must resent unackowledged
           packets.
           The second decides after how mant failed attempts
           to drop the packet and transmit the next.
        */
        radio.setRetries(15,0);

        /* This is done as a simple caliberation.
           Start ad stop listening configures the moules.
        */
        radio.startListening();
        radio.stopListening();

        /* This sets the channel at which the radio operates.
           Ensure that the sender and receiver channel work
           at the same channel.
           Select one channel from 0-127.
           Ensure your local laws allow the channel you're using.
           EG: America bans channels abone 83~
        */
        radio.setChannel(0x4c);

        /*Set power amplifier levels.
          Argument could be one of four values.
          I.e, RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm,
          RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
        */
        radio.setPALevel(RF24_PA_MAX);

        //radio.openWritingPipe(pipes[1]);

        /* Open an innternal reading pipe.
           First argument defines how many pipes can be opened
           in each channel. Upto 6 channels can be opened.
           The second defines a hex adress that is internal
           to your platform.
        */
        radio.openReadingPipe(1,pipes[0]);

        /* Start listening to incoming packets on specified channl
           and specified port numbers.
        */
        radio.startListening();
        radio.printDetails();
}

void loop()
{
        char *msg;

        if (radio.available(pipes[0])){
                radio.read(msg, sizeof(msg));
                printf("Payload : %s\n", msg);
        } else {
                printf("EAT A CAT\n");
        }
}

int main(int argc, char** argv)
{
        setup();
        while(1)
                loop();

        return 0;
}
