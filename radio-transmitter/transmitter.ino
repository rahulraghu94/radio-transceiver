
#include <RH_ASK.h>
#include <Wire.h>
#include <SPI.h> 

RH_ASK driver;
//char *in = NULL;

String in;
char *msg;

void setup()
{
    Serial.begin(9600);   // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}
void loop()
{
     while (Serial.available() > 0) {
                in = Serial.readString();
        }
    
    in.toCharArray(msg, sizeof(msg));
    driver.send((uint8_t *)msg, (strlen(msg)));
    driver.waitPacketSent();

    Serial.print("Packet sent! Message was: "); Serial.println(in);
    
    delay(200);
}

