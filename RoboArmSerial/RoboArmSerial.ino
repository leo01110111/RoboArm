#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates. Leo's Note: Work for the MG996R Servo

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ); 
  delay(10);
}

void loop(){

  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int base = Serial.parseInt();
    //and the next...
    int shoulder = Serial.parseInt();
    int elbow = Serial.parseInt();
    int wrist1 = Serial.parseInt();
    int wrist2 = Serial.parseInt();
    int wrist3 = Serial.parseInt();

    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      //in case an out of bounds angle was sent
      base = constrain(base, 0, 180);
      shoulder = constrain(shoulder, 0, 255);
      elbow = constrain(elbow, 0, 270);
      wrist1 = constrain(wrist1, 0, 270);
      wrist2 = constrain(wrist2, 0, 180);
      wrist3 = constrain(wrist3, 0, 180);

      //Update joint positions
      base(base);
      shoulder(shoulder);
      elbow(elbow);
      wrist1(wrist1);
      wrist2(wrist2);
      wrist3(wrist3);

      Serial.println("Joints Updated")
    }
  }

}

void SGServoControl(int pin, int degree){ //control function for the 2 claw servos 0-180 degrees
  const int servomin = 100;// This is the 'minimum' pulse length count (out of 4096) 120
  const int servomax = 445;// This is the 'maximum' pulse length count (out of 4096) 
  int pulse = map(degree, 0, 180, servomin, servomax);
  pwm.setPWM(pin, 0, pulse);
  
}

void MGServoControl(int pin, int degree){ //control function for MG996r servos 0-180 degrees
  const int servomin = 120;// This is the 'minimum' pulse length count (out of 4096) 120
  const int servomax = 470;// This is the 'maximum' pulse length count (out of 4096) 494 prev slip a four of the time
  int pulse = map(degree, 0, 180, servomin, servomax);
  pwm.setPWM(pin, 0, pulse);
}

void DSServoControl(int pin ,int degree){ //control function for DS3218 servos 0-270
  const int servomin = 120;// This is the 'minimum' pulse length count (out of 4096)
  const int servomax = 500;// This is the 'maximum' pulse length count (out of 4096)
  int pulse = map(degree, 0, 270, servomin, servomax);
  pwm.setPWM(pin, 0, pulse);
}

void TDServoControl(int pin, int degree){ //control function for TD-8160MG servos 0-255
  const int servomin = 65;// This is the 'minimum' pulse length count (out of 4096)
  const int servomax = 500;// This is the 'maximum' pulse length count (out of 4096)
  int pulse = map(degree, 0, 255, servomin, servomax);
  pwm.setPWM(pin, 0, pulse);
}

void base(int degree){
  MGServoControl(8, degree);
}
void shoulder(int degree){
  TDServoControl(9, degree);
}
void elbow(int degree){
  DSServoControl(10, 270-degree);
}
void wrist1(int degree){
  DSServoControl(11, 270-degree);
}
void wrist2(int degree){
  MGServoControl(12, 270-degree);
}
void wrist3(int degree){
  MGServoControl(13, 270-degree);
}

void grip(bool status){
  if(status){
    SGServoControl(14,70);
    SGServoControl(15,70);
  }
  else{
    SGServoControl(14,0);
    SGServoControl(15,0);
  }
}

void upright(){
  //Base - 0
  MGServoControl(8,0);
  //Shoulder - 1
  TDServoControl(9, 120);
  //Elbow - 2
  DSServoControl(10, 135);
  //Yaw - 3
  DSServoControl(11,0);
  //Pitch - 4
  MGServoControl(12,60);
  //Roll - 5
  MGServoControl(13,90);
}

