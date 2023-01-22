#include <AFMotor.h>
#include <Servo.h>
Servo ms;
int trig=A2;
int echo=A1;
int duration;
float dL,dF,dR,d;
float meter;
AF_DCMotor motor(3);
AF_DCMotor motr(2);
void setup()
{
  ms.attach(10);
  motor.setSpeed(250);
  motr.setSpeed(250);
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  ms.write(90);
  delay(1000);
  Serial.println("Distance:");
}

void loop(){
  ms.write(90);
  delay(1000);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trig, LOW);
  d = pulseIn(echo, HIGH);
  dF=d/58;
  Serial.print("dF: ");
  Serial.println(dF);
  if(dF<40){
    motor.run(RELEASE);
    motr.run(RELEASE);
    ms.write(180);
    delay(1000);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trig, LOW);
    d = pulseIn(echo, HIGH);
    dL=d/58;
    
    ms.write(0);
    delay(1000);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trig, LOW);
    d = pulseIn(echo, HIGH);
    dR=d/58;
    if(dR>40){
      motor.run(BACKWARD);
      motr.run(RELEASE);
    delay(1300);
      //motr.run(FORWARD);
      //motor.run(FORWARD);
      
      //motr.run(RELEASE);
    }else if(dL>40){
      motr.run(BACKWARD);
      motor.run(RELEASE);
    delay(1300);
      //motor.run(FORWARD);
      //motr.run(FORWARD);
      //motr.run(RELEASE);
    }else{
      motr.run(BACKWARD);
      motor.run(BACKWARD);
    }
      //motr.run(RELEASE);
      //motor.run(RELEASE);

  }else{
    motor.run(FORWARD);
    motr.run(FORWARD);
  }
}