#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates. 20ms (millisecond) period

void setup() {
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}

void loop() { 
  //For tuning servo pulses
  open();
  delay(2000);
  close();
  delay(2000);
}

void MGServoControl(int pin, int degree){ //control function for MG996r servos 0-180 degrees
  const int servomin = 544;// This is pulse length in microseconds for min position
  const int servomax = 2250;// This is pulse length in microseconds for max position
  int ms = map(degree, 0, 180, servomin, servomax); //command in microseconds
  pwm.writeMicroseconds(pin,ms);
}

void DSServoControl(int pin ,int degree){ //control function for DS3218 servos 0-270
  const int servomin = 500;// This is pulse length in microseconds for min position
  const int servomax = 2350;// This is pulse length in microseconds for max position
  int ms = map(degree, 0, 270, servomin, servomax); //command in microseconds
  pwm.writeMicroseconds(pin,ms);
}

void TDServoControl(int pin, int degree){ //control function for TD-8160MG servos 0-255
  const int servomin = 500;// This is pulse length in microseconds for min position
  const int servomax = 2410;// This is pulse length in microseconds for max position
  int ms = map(degree, 0,270, servomin, servomax); //command in microseconds
  pwm.writeMicroseconds(pin,ms);
}

void SGServoControl(int pin, int degree){ //control function for the 2 claw servos 0-180 degrees
  const int servomin = 500;// This is pulse length in microseconds for min position
  const int servomax = 2400;// This is pulse length in microseconds for max position
  int ms = map(degree, 0,180, servomin, servomax); //command in microseconds
  pwm.writeMicroseconds(pin,ms);
}

void open(){
  SGServoControl(14,0);
  SGServoControl(15,0);
}

void close(){
  SGServoControl(14,60);
  SGServoControl(15,60);
}
