#include <Servo.h>
Servo myservo1;
Servo myservo2;

int motor1EnA = 10; // Enable para Motor 1
int motor1In1 = 9; // Control de dirección 1 para Motor 1
int motor1In2 = 8; // Control de dirección 2 para Motor 1
int motor2EnA = 5; // Enable para Motor 2
int motor2In1 = 6; // Control de dirección 1 para Motor 2
int motor2In2 = 7; // Control de dirección 2 para Motor 2
const int Trigger1 = 12;
const int Echo1 = 13;
const int Trigger2 = 2;
const int Echo2 = 4;
void setup() {
  Serial.begin(9600);
  myservo1.attach(3);
  myservo2.attach(11);
  pinMode(motor1EnA, OUTPUT);
  pinMode(motor1In1, OUTPUT);
  pinMode(motor1In2, OUTPUT);
  pinMode(motor2EnA, OUTPUT);
  pinMode(motor2In1, OUTPUT);
  pinMode(motor2In2, OUTPUT);
  pinMode(Trigger1, OUTPUT);
  pinMode(Echo1, INPUT);
  digitalWrite(Trigger1, LOW);
  pinMode(Trigger2, OUTPUT);
  pinMode(Echo2, INPUT);
  digitalWrite(Trigger2, LOW);
}

void loop() {
  long d1 = obtenerDistancia(Trigger1, Echo1);
  long d2 = obtenerDistancia(Trigger2, Echo2);
  if (d1 > 10 || d2 > 10) {
      Adelante();
  }else {
    Parar();
    delay(500)
    Retrocerder();
  }
  if (Serial.available() > 0) { 
    char comando = Serial.read(); 
    if (comando == 'O') {
      Parar(); 
      angulo = 0; 
      myservo.write(angulo); 
      delay(500); 
    } 
    else if (comando == 'C') { 
      angulo = 90; 
      myservo.write(angulo); 
      delay(500); 
    }
  }
}

void Adelante(){
  digitalWrite(motor1In1, HIGH);
  digitalWrite(motor1In2, LOW);
  analogWrite(motor1EnA, 100);
  digitalWrite(motor2In1, HIGH);
  digitalWrite(motor2In2, LOW);
  analogWrite(motor2EnA, 100);
  delay(10)
}
void Retroceder(){
  digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor2In1, HIGH);
  digitalWrite(motor2In2, LOW);
  analogWrite(motor2EnA, 100);
  delay(300)
}
void Parar(){
  digitalWrite(motor1EnA, LOW);
  digitalWrite(motor2EnA, LOW);
}


long obtenerDistancia(int Trigger, int Echo) {
  long t;
  long d;

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH);
  d = t / 59;
  return d;
}


