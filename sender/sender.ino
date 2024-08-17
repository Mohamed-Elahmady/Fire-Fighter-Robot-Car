/*
  1 - GND
  2 - VCC 3.3V !!! NOT 5V
  3 - CE to Arduino pin 9
  4 - CSN to Arduino pin 10
  5 - SCK to Arduino pin 13
  6 - MOSI to Arduino pin 11
  7 - MISO to Arduino pin 12
  8 - UNUSED
*/

/* Import needed Libraries */
#include <SPI.h>       // SPI Library
#include <nRF24L01.h>  // NRF24L01 Library
#include <RF24.h>      // RF24 Library

/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10

#define up      2
#define right   3
#define down    4
#define left    5

#define start   6
#define select  7
#define analog  8

#define x       A0
#define y       A1





// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t pipe = 0xE24E23F22F21E18LL; // Define the transmit pipe
//const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

/*-----( Declare Variables )-----*/
int data[9];
// array     0     1    2      3           4         5        6          7           8 
//           x     y    up     right      down      left     start     select      analog
//           A0    A1   D2     D3          D4         D5      D6         D7          D8   


void setup() {
  Serial.begin(9600);
  radio.begin(); // Initializing NRF24L01 Module
  radio.openWritingPipe(pipe); // For Transmitting Operation, Must OpenWritingPipe
   for(int i=2;i<9;i++)
  {
    pinMode(i,INPUT_PULLUP);
  }

  pinMode(x, INPUT);
  pinMode(y, INPUT);
}

/// array     0     1    2      3         4           5        6          7           8 
//            x     y    up    right      down      left     start     select      analog
//            A0    A1   D2     D3        D4         D5        D6        D7          D8   

void loop() {
  data[0] =analogRead(x);
  data[1] =analogRead(y);


  for(int j=2;j<9;j++)
  {
    data[j]=digitalRead(j);
  }


  Serial.print("X: ");
  Serial.print(data[0]);
  Serial.print(" Y: ");
  Serial.print(data[1]);

  Serial.print("    up: ");
  Serial.print(data[2]);

  Serial.print(" right: ");
  Serial.print(data[3]);

  Serial.print("    down: ");
  Serial.print(data[4]);

  Serial.print(" left: ");
  Serial.print(data[5]);

  Serial.print("    start: ");
  Serial.print(data[6]);

  Serial.print(" select: ");
  Serial.print(data[7]);

   Serial.print("    analog: ");
   Serial.println(data[8]);





  radio.write(&data, sizeof(data)); // Send the data array
  delay(100); // Add a small delay to prevent flooding the receiver
}
