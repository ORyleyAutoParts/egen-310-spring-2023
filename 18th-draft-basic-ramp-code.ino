#include <DRV8835MotorShield.h>
#include <Servo.h>

int dir1 = 7;
int dir2 = 8;

int spd1 = 9;
int spd2 = 10;

Servo Lservo;  // create servo object to control a servo
Servo Aservo;
int hi = 0;  // variable to store the servo position

void setup() {

  Serial.begin(9600);
  Lservo.attach(11);  // attaches the servo on pin 11 to the servo object
  Aservo.attach(5);
  Serial.println("Driving!");

  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(spd1, OUTPUT);
  pinMode(spd2, OUTPUT);

  Lservo.write(30);
  Aservo.write(40);
  delay(1000);

  for (hi = 30; hi <= 60; hi += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Lservo.write(hi);  // tell servo to go to position in variable 'pos'
    delay(15);         // waits 15ms for the servo to reach the position
  }

  delay(5000);

  digitalWrite(dir1, 0);
  digitalWrite(spd1, 1);
  digitalWrite(dir2, 0);
  digitalWrite(spd2, 1);
  delay(2000);
  digitalWrite(dir1, 1);
  digitalWrite(spd1, LOW);
  digitalWrite(dir2, 1);
  digitalWrite(spd2, LOW);
  delay(200000);
}

void loop() {}
