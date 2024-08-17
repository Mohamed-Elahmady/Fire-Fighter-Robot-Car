#define JOYSTICK_X A0
#define JOYSTICK_Y A1

#define A 2
#define B 3
#define C 4
#define D 5


#define JOYSTICK_THRESHOLD 100

void setup() {
  pinMode(A , INPUT_PULLUP);
  pinMode(B , INPUT_PULLUP);
  pinMode(C , INPUT_PULLUP);
  pinMode(D , INPUT_PULLUP);

}

void loop() {
  int x = analogRead(JOYSTICK_X);
  int y = analogRead(JOYSTICK_Y);
  int SERVO_X_Positive = digitalRead(B);
  int SERVO_X_Negative = digitalRead(D);
  int PUMP_Motor = digitalRead(A)
  MoveForward(y);
  MoveBack(y);
  MoveRight(x,y);
  MoveLeft(x,y);
  SERVO_X_P (SERVO_X_Positive);
  SERVO_X_N (SERVO_X_Negative);
  PUMP_ON(PUMP_Motor);
}
/*********** OTHMAN Link ******************/
void MoveForward(int Y)
{
  if(Y > (512 + JOYSTICK_THRESHOLD))
  {
    // Motors Move Forward
  }
}
void MoveBack(int Y)
{
  if(Y < (512 - JOYSTICK_THRESHOLD))
  {
    // Motors Move Back
  }
  if(X > (512 + JOYSTICK_THRESHOLD) &&  (Y < (512 - JOYSTICK_THRESHOLD))
  {
    // Motors Move Back
  }
  if(X < (512 - JOYSTICK_THRESHOLD) &&  (Y < (512 - JOYSTICK_THRESHOLD))
  {
    // Motors Move Back
  }
}
void MoveRight(int X , int Y)
{
  if(X > (512 + JOYSTICK_THRESHOLD) )
  {
    // Motors Move Right
  }
  if(X > (512 + JOYSTICK_THRESHOLD) &&  (Y > (512 + JOYSTICK_THRESHOLD))
  {
    // Motors Move Right
  }
}
void MoveLeft(int X , int Y)
{
  if(X < (512 - JOYSTICK_THRESHOLD) )
  {
    // Motors Move left
  }
  if(X < (512 + JOYSTICK_THRESHOLD) &&  (Y > (512 + JOYSTICK_THRESHOLD))
  {
    // Motors Move left
  }
}
/*********** MAZEN implement ******************/
/*********** OTHMAN Link ******************/
void SERVO_X_P (int SP)
{
  if(SP == LOW)
  {
    // servo move right 
  }
  else
  {
    // servo motor return to original position
  }
}
void SERVO_X_N (int SN)
{
  if(N == LOW)
  {
    // servo move left
  }
  else
  {
    // servo motor return to original position
  }
}
/*********** SAMIR implement ******************/
/*********** OTHMAN Link ******************/
void PUMP_ON(int PM)
{
  if(PM == LOW)
  {
    // PUMP Motor turn on
  }
  else
  {
    // PUMP Motor turn off
  }
}