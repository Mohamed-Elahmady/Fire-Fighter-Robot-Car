#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Servo.h"


/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN  10

#define A1 2 // Right motors forward pin
#define A2 4 // Right motors backward pin
#define B1 7 // Left motors forward pin
#define B2 8 // Left motors backward pin
// #define ENA 3 // Right motors speed control pin
// #define ENB 5 // Left motors speed control pin


/*-----( Declare objects )-----*/
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio object

Servo myservo ; //   Create a Servo object



#define servo 6 
#define PUMP  3

#define JOYSTICK_THRESHOLD 100
#define servoStep           15


const uint64_t pipe = 0xE24E23F22F21E18LL; // Define the pipe

int income[9], servoAngle, x, y; 
bool servoMoveRight, servoMoveLeft, pump, Race_Speed, Fire_speed;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  // Initialize pin modes
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  // pinMode(ENA, OUTPUT);
  // pinMode(ENB, OUTPUT);
  pinMode(PUMP, OUTPUT);
  
  // Speed1(); // Set initial speed

  myservo.attach(servo); // Attach servo to pin
  myservo.write(90); // Set initial servo position

  if (!radio.begin()) { // Check if radio hardware is responding
    Serial.println("Radio hardware is not responding!");
    while (1); // Halt execution if radio is not responding
  }
  radio.openReadingPipe(1, pipe); // Open the reading pipe
  radio.startListening(); // Start listening for incoming data
}

void loop() {
/////////////////////////////////////////////////////////////////////////////////////////////////////
//                           Array indexes for incoming data                                       //
//                                                                                                 //
//           0       1       2        3         4         5         6         7           8        //
//           x       y       up     right      down      left     start     select      analog     //
//                                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////////////////////
 
  if (radio.available()) { // Check if there is incoming data
    print_income_data(); // Print incoming data for debugging
    radio.read(income, sizeof(income)); // Read the incoming data into the income array
    x = income[0]; // Assign x value
    y = income[1]; // Assign y value
    
    pump = income[2]; // Assign pump value
    servoMoveRight = income[3]; // Assign servoMoveRight value
    servoMoveLeft = income[5]; // Assign servoMoveLeft value

    Fire_speed = income[6]; // Assign Fire_speed value
    Race_Speed = income[7]; // Assign Race_Speed value

    ControlMovement(x, y); // Control robot movement based on joystick input

    Pump(); // Control the pump
    RotateServo(); // Control the servo

    // if (!Race_Speed) Speed1(); // Set speed based on Race_Speed
    // if (!Fire_speed) Speed2(); // Set speed based on Fire_speed
  }
}

//////////////////////////////////////////////////////////////////////////////////////////
//                          Control The movement using the JOYSTICK                     //
//////////////////////////////////////////////////////////////////////////////////////////

void ControlMovement(int X, int Y) {
  if (Y > (512 + JOYSTICK_THRESHOLD)) {
    MoveForward(); // Move forward if joystick is pushed forward
  } else if (Y < (512 - JOYSTICK_THRESHOLD)) {
    MoveBack(); // Move backward if joystick is pulled back
  } else if (X > (512 + JOYSTICK_THRESHOLD)) {
    MoveRight(); // Move right if joystick is pushed right
  } else if (X < (512 - JOYSTICK_THRESHOLD)) {
    MoveLeft(); // Move left if joystick is pushed left
  } else {
    Stop(); // Stop if joystick is in neutral position
  }
}

// void Speed1() {          // Set speed based on Race_Speed
//   analogWrite(ENA, 255); // Set speed for right motors
//   analogWrite(ENB, 255); // Set speed for left  motors
// }

// void Speed2() {          // Set speed based on Fire_speed
//   analogWrite(ENA, 165); // Set speed for right motors
//   analogWrite(ENB, 165); // Set speed for left  motors
// }

void MoveForward() {
  digitalWrite(A1, HIGH); // Move right motors forward
  digitalWrite(A2, LOW);  // Move right motors forward
  digitalWrite(B1, HIGH); // Move left  motors forward
  digitalWrite(B2, LOW);  // Move left  motors forward
}

void MoveBack() {
  digitalWrite(A1, LOW);  // Move right motors backward
  digitalWrite(A2, HIGH); // Move right motors backward
  digitalWrite(B1, LOW);  // Move left  motors backward
  digitalWrite(B2, HIGH); // Move left  motors backward
}

void MoveRight() {
  digitalWrite(A1, HIGH); // Move right motors forward
  digitalWrite(A2, LOW);  // Move right motors forward
  digitalWrite(B1, LOW);  // Move left  motors backward
  digitalWrite(B2, HIGH); // Move left  motors backward
}

void MoveLeft() {
  digitalWrite(A1, LOW);  // Move right motors backward
  digitalWrite(A2, HIGH); // Move right motors backward
  digitalWrite(B1, HIGH); // Move left  motors forward
  digitalWrite(B2, LOW);  // Move left  motors forward
}

void Stop() {
  digitalWrite(A1, LOW); // Stop right motors
  digitalWrite(A2, LOW); // Stop right motors
  digitalWrite(B1, LOW); // Stop left  motors
  digitalWrite(B2, LOW); // Stop left  motors
}
void RotateServo() {
  servoAngle = myservo.read(); // Read current servo angle
  if (!servoMoveRight) myservo.write(servoAngle + servoStep); // Move servo right
  if (!servoMoveLeft) myservo.write(servoAngle - servoStep);  // Move servo left
}

void Pump() {
  if (!pump) {
    digitalWrite(PUMP, HIGH); // Turn on the pump
  } else {
    digitalWrite(PUMP, LOW); // Turn off the pump
  }
}

void print_income_data() {
  // Print incoming data for debugging
  Serial.print("X: ");
  Serial.print(income[0]);
  Serial.print(" Y: ");
  Serial.print(income[1]);

  Serial.print("    up: ");
  Serial.print(income[2]);

  Serial.print(" right: ");
  Serial.print(income[3]);

  Serial.print("    down: ");
  Serial.print(income[4]);

  Serial.print(" left: ");
  Serial.print(income[5]);

  Serial.print("    start: ");
  Serial.print(income[6]);

  Serial.print(" select: ");
  Serial.print(income[7]);

  Serial.print("    analog: ");
  Serial.println(income[8]);
}
