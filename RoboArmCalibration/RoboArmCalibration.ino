#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates. Leo's Note: Work for the MG996R Servo

void SGServoControl(int pin, int degree){ //control function for the 2 claw servos 0-180 degrees
  const int servomin = 100;// This is the 'minimum' pulse length count (out of 4096) 120
  const int servomax = 445;// This is the 'maximum' pulse length count (out of 4096) 
  int pulse = map(degree, 0, 180, servomin, servomax);
  pwm.setPWM(pin, 0, pulse);
  
}

void RollServoControl(int pin, int degree){ //control function for 5th servo 0-180 degrees
  const int servomin = 300;// This is the 'minimum' pulse length count (out of 4096) 120
  const int servomax = 350;// This is the 'maximum' pulse length count (out of 4096) 494 prev slip a four of the time
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

void open(){
  SGServoControl(14,0);
  SGServoControl(15,0);
}

void close(){
  SGServoControl(14,70);
  SGServoControl(15,70);
}

void snap(){
  open();
  delay(1000);
  close();
  delay(1000);
}

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

String input;
bool toggle = false;
int turn = 200;

void loop() {
  //the calibration begins
  eat();
}

void base(int degree){
  MGServoControl(8, degree);
}
void shoulder(int degree){
  TDServoControl(9, degree);
}

void eat(){
  //Base - 0
  MGServoControl(8,0);
  //Shoulder - 1
  TDServoControl(9, 120);
  //Elbow - 2
  DSServoControl(10, 135);
  //Yaw - 3
  DSServoControl(11,0);
  //Pitch - 4
  MGServoControl(12,90);
  //Roll - 5
  MGServoControl(13,90);
  //Claw
  //snap();
}
