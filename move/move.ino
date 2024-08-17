#define N1 2
#define N2 4
#define N3 7
#define N4 8
#define ENA 3  
#define ENB 5


void setup() {
  pinMode(N1,OUTPUT);
  pinMode(N1,OUTPUT);
  pinMode(N3,OUTPUT);
  pinMode(N4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

}

void loop() {
  analogWrite(ENA, 255);
    analogWrite(ENB, 255);
  Forward();
  delay(5000);
  Backward();
  delay(5000);
  Right();
  delay(5000);
  Left();
  delay(5000);
  Stop();
  delay(1000);


}

void Forward(void)
{
  digitalWrite(N1,HIGH);
  digitalWrite(N2,LOW);
  digitalWrite(N3,HIGH);
  digitalWrite(N4,LOW);

}
void Backward(void)
{
  digitalWrite(N1,LOW);
  digitalWrite(N2,HIGH);
  digitalWrite(N3,LOW);
  digitalWrite(N4,HIGH);

}
void Right(void)
{
  digitalWrite(N1,HIGH);
  digitalWrite(N2,LOW);
  digitalWrite(N3,LOW);
  digitalWrite(N4,HIGH);

}
void Left(void)
{
  digitalWrite(N1,LOW);
  digitalWrite(N2,HIGH);
  digitalWrite(N3,HIGH);
  digitalWrite(N4,LOW);

}
void Stop(void)
{
  digitalWrite(N1,LOW);
  digitalWrite(N2,LOW);
  digitalWrite(N3,LOW);
  digitalWrite(N4,LOW);

}

