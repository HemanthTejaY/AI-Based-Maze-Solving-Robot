#include <AFMotor.h>
AF_DCMotor motor_l(2);
AF_DCMotor motor_r(4);

#define trigPin3 44
#define echoPin3 45
#define trigPin1 42
#define echoPin1 43
#define trigPin2 40
#define echoPin2 41
 
String path="";

long duration,distance,RightSensor,BackSensor,FrontSensor,LeftSensor;

void stopmove()
{
  motor_l.run(RELEASE);
  motor_r.run(RELEASE);
}

void initializeSpeed()
{
  motor_l.setSpeed(200);
  motor_r.setSpeed(200);
}


void turnRight()
{
  motor_l.run(FORWARD);
  motor_r.run(BACKWARD);
  delay(300);
  motor_l.run(RELEASE);
  motor_r.run(RELEASE);
}
  
void turnLeft()
{
  motor_l.run(BACKWARD);
  motor_r.run(FORWARD);
  delay(300);
  motor_l.run(RELEASE);
  motor_r.run(RELEASE);
}

void goStraight()
{
  motor_l.run(FORWARD);
  motor_r.run(FORWARD);
  delay(300);
  motor_l.run(RELEASE);
  motor_r.run(RELEASE);
}

void takeUturn()
{
  SonarSensor(trigPin1, echoPin1);
  FrontSensor = distance;
  while(FrontSensor < 10)
  {
    motor_l.run(FORWARD);
    motor_r.run(BACKWARD);
    delay(600);
    motor_l.run(RELEASE);
    motor_r.run(RELEASE);
  }
}


void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
//delayMicroseconds(2);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1; 
}
 
void setup()
{
Serial.begin (9600);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
}
 
void loop() {

SonarSensor(trigPin2, echoPin2);
RightSensor = distance;
SonarSensor(trigPin3, echoPin3);
LeftSensor = distance;
SonarSensor(trigPin1, echoPin1);
FrontSensor = distance;
 
Serial.print(LeftSensor);
Serial.print(" - ");
Serial.print(FrontSensor);
Serial.print(" - ");
Serial.println(RightSensor);

if ((LeftSensor>20) && (RightSensor>20) && (FrontSensor>20)) 
{
  Serial.println("Movement");
  initializeSpeed();
  goStraight();
}

else if ((LeftSensor>20) && (RightSensor>20) && (FrontSensor<20))
{
   //stopmove();
   Serial.println("Left Turn");
   initializeSpeed();
   turnLeft();
   path=path+"L";
   //path=path+"S";
}
else if ((LeftSensor>20) && (RightSensor<20) && (FrontSensor>20))
{
   //stopmove();
   Serial.println("Left Turn");
   initializeSpeed();
   turnLeft();
   path=path+"L";
}
else if ((LeftSensor<20) && (RightSensor>20) && (FrontSensor>20))
{
   //stopmove();
   Serial.println("Straight");
   initializeSpeed();
   goStraight();
   path=path+"S";
}
else if ((LeftSensor<20) && (RightSensor<20) && (FrontSensor>20))
{
   //stopmove();
   Serial.println("Straight Turn");
   initializeSpeed();
   goStraight();
   path=path+"S";
}
else if ((LeftSensor<20) && (RightSensor>20) && (FrontSensor<20))
{
   //stopmove();
   Serial.println("Right Turn");
   initializeSpeed();
   turnRight();
   path=path+"R";
}
else if ((LeftSensor>20) && (RightSensor<20) && (FrontSensor<20))
{
   //stopmove();
   Serial.println("Left Turn");
   initializeSpeed();
   turnLeft();
   path=path+"L";
}
else
{
   //stopmove();
   Serial.println("U-Turn");
   initializeSpeed();
   takeUturn();
   path=path+"R";
}

//delay(200);

}
