#include <SPI.h>
#include "RF24.h"

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
byte addresses[][6] = {"1Node","2Node"};
const uint64_t receiverAddress = 0xABCDABCD71LL; 
int packet_count = 0;
/* Packet count keeps track of the number of packets sent across.
 * The current system will expect an ack for every 100 (?) sent across.
 * This is a simple way to know weather the connection is still alive or not.
 * For every 100th packet sent across, we will wait for an ack, check for a
 * time out and report weather connection is alive or not.
 */

void setup()
{
        Serial.begin(115200);
        radio.begin();

        // SetRetries(Delay before resending, Attemps before giving up)
        radio.setRetries(15,15);

        //Caliberate?
        radio.startListening();
        radio.stopListening();
        /*
         *  Setting to low to overcome power supply related issues. Also since there's
         *  likelihood of close proximity of the devices. RF24_PA_MAX is default.
         */
        radio.setPALevel(RF24_PA_MAX);
        radio.setChannel(0x4c);

        // Start the radio listening for data for connect information
        radio.stopListening();
        
        // Open a writing and reading pipe on each radio, with opposite addresses
        radio.openWritingPipe(receiverAddress);        
}

void loop()
{
        //Control signal with throttle roll, pitch and yaw values with $ delimiter
        String cont_sig = "t0 r0 p0 y0$";

        //Convert sont_sig string to char array to send across
        char *msg;

        /*
         * Program will continue sending 0 values till new values entered
         * from serial. When datat from stdIO is avalable, read them in as
         * a string, convert to char array and send across. The new values
         * will then be sent continuously.
         */
        if(Serial.available()){
                cont_sig = Serial.readString();
        }

        cont_sig.toCharArray(msg, sizeof(cont_sig));

        /* "Stop listening so that we can start talking"
         * -- Worst public speaking advice ever
         */
        radio.stopListening();

        if (!radio.write( &msg, sizeof(msg))){
                Serial.println(F("failed to send"));
        } else {
                Serial.println("Success");
        }

        packet_count++;
        Serial.println(packet_count);

        
        delay(1000);
}
