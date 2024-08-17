#define Pump_pin 1
#define Button_A 2
#define Noise 50

int last_state = HIGH;
unsigned long last_time = 0;

void setup() {
  pinMode(Button_A , INPUT_PULLUP);
  pinMode(Pump_pin , OUTPUT);
  digitalWrite(Pump_pin , LOW);

}

void loop() {
  int Button_State  = digitalRead(Button_A);
  //PUMP_Turn(Button_State);
  if(Button_State != last_state){
    last_time = millis();
  }
  if((millis()-last_time) > Noise){
    if(Button_State != last_state){
      last_state = Button_State;
      PUMP_Turn(Button_State);
    }
  }

}

void PUMP_Turn(int State){
  if (State == LOW) {
    digitalWrite(Pump_pin, HIGH);
  }
  else {
    digitalWrite(Pump_pin, LOW);
  }
}