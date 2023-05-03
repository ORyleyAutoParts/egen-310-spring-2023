#include <DRV8835MotorShield.h>
#include <Servo.h>

int dir1 = 7;
int dir2 = 8;

int spd1 = 9;
int spd2 = 10;

Servo Lservo;  // create servo object to control a servo
Servo Aservo;
int hi = 0;  // variable to store the servo position

DRV8835MotorShield motors;

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

  for (hi = 30; hi <= 80; hi += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Lservo.write(hi);  // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15ms for the servo to reach the position
  }

  delay(2000);

  for (hi = 40; hi <= 200; hi += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Aservo.write(hi);  // tell servo to go to position in variable 'pos'
    delay(15);          // waits 15ms for the servo to reach the position
  }

  /*for (int speed = 0; speed <= 400; speed++)
  {
    motors.setM1Speed(speed);
    //motors.setM2Speed(speed);
    delay(5);
  }
  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setM1Speed(speed);
    //motors.setM2Speed(speed);
    delay(2);
  }*/

  
  digitalWrite(dir1, 0);
  digitalWrite(spd1, HIGH);
  digitalWrite(dir2, 0);
  digitalWrite(spd2, HIGH);
  delay(500);
  digitalWrite(dir1, 1);
  digitalWrite(spd1, LOW);
  digitalWrite(dir2, 1);
  digitalWrite(spd2, LOW);
  delay(2000);

  for (hi = 200; hi >= 40; hi -= 1) {  // goes from 180 degrees to 0 degrees
    Aservo.write(hi);                    // tell servo to go to position in variable 'pos'
    delay(15);                            // waits 15ms for the servo to reach the position
  }

  delay(2000);

  for (hi = 60; hi >= 30; hi -= 1) {  // goes from 180 degrees to 0 degrees
    Lservo.write(hi);                   // tell servo to go to position in variable 'pos'
    delay(15);                           // waits 15ms for the servo to reach the position
  }

  delay(2000);

  /*for (int speed = 0; speed >= -400; speed--)
  {
    motors.setM1Speed(speed);
    motors.setM2Speed(speed);
    delay(5);
  }
  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setM1Speed(speed);
    motors.setM2Speed(speed);
    delay(2);
  }*/

  digitalWrite(dir1, 1);
  digitalWrite(spd1, HIGH);
  digitalWrite(dir2, 1);
  digitalWrite(spd2, HIGH);
  delay(3000);
  digitalWrite(dir1, 1);
  digitalWrite(spd1, LOW);
  digitalWrite(dir2, 1);
  digitalWrite(spd2, LOW);
  delay(2000000);
}

void loop() {

  /*digitalWrite(dir1, 1);
  digitalWrite(spd1, HIGH);
  digitalWrite(dir2, 1);
  digitalWrite(spd2, HIGH);
  delay(2000);
  digitalWrite(dir1, 1);
  digitalWrite(spd1, LOW);
  digitalWrite(dir2, 1);
  digitalWrite(spd2, LOW);
  delay(2000000);  */
}
