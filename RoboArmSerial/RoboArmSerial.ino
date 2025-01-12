#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_FREQ 50  // Analog servos run at ~50 Hz updates. Leo's Note: Work for the MG996R Servo

void setup() {
  Serial.begin(9600);

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  delay(10);
}

void loop() {
  if (Serial.available() > 0) {
    String msg = Serial.readString();
    if (msg[0] == 'J') {
      int jointAngles[7];
      parseJoints(msg, jointAngles, 7);
      setJoints(jointAngles);
      Serial.println("Joints Updated");
    }
  }
}

void parseJoints(String input, int* outputArray, int arraySize) {
  int currentIndex = 0;  // Index for the output array

  // Start parsing from the second character to skip the initial letter
  int startIdx = 1;  // Skip the first character (the letter)

  // Use a while loop to extract integers
  while (currentIndex < arraySize) {
    // Find the next comma
    int endIdx = input.indexOf(',', startIdx);

    // If no more commas, extract the last number
    if (endIdx == -1) {
      endIdx = input.length();
    }

    // Extract the substring, convert to int, and store in the array
    String numberStr = input.substring(startIdx, endIdx);
    outputArray[currentIndex] = numberStr.toInt();

    // Move to the next segment
    startIdx = endIdx + 1;
    currentIndex++;
  }
}

void setJoints(int jointAngles[]) {

  jointAngles[0] = constrain(jointAngles[0], 0, 180);  //base
  jointAngles[1] = constrain(jointAngles[1], 0, 255);  //shoulder
  jointAngles[2] = constrain(jointAngles[2], 0, 270);  //elbow
  jointAngles[3] = constrain(jointAngles[3], 0, 270);  //wrist 1
  jointAngles[4] = constrain(jointAngles[4], 0, 180);  //wrist 2
  jointAngles[5] = constrain(jointAngles[5], 0, 180);  //wrist 3
  jointAngles[6] = constrain(jointAngles[6], 0, 1);    //gripper

  //debug(jointAngles, 7);

  base(jointAngles[0]);
  shoulder(jointAngles[1]);
  elbow(jointAngles[2]);
  wrist1(jointAngles[3]);
  wrist2(jointAngles[4]);
  wrist3(jointAngles[5]);
  gripper(jointAngles[6]);
}

void debug(int jointAngles[], int length){
  for (int i = 0; i < length; i++) {
    Serial.print(String(jointAngles[i]) + " ");

    if (i == length-1) {
      Serial.print("\n");
    }
  }
}

void SGServoControl(int pin, int degree) {  //control function for the 2 claw servos 0-180 degrees
  const int servomin = 100;                 // This is the 'minimum' pulse length count (out of 4096) 120
  const int servomax = 445;                 // This is the 'maximum' pulse length count (out of 4096)
  int pulse = map(degree, 0, 180, servomin, servomax);
  pwm.setPWM(pin, 0, pulse);
}

void MGServoControl(int pin, int degree) {  //control function for MG996r servos 0-180 degrees
  const int servomin = 120;                 // This is the 'minimum' pulse length count (out of 4096) 120
  const int servomax = 470;                 // This is the 'maximum' pulse length count (out of 4096) 494 prev slip a four of the time
  int pulse = map(degree, 0, 180, servomin, servomax);
  pwm.setPWM(pin, 0, pulse);
}

void DSServoControl(int pin, int degree) {  //control function for DS3218 servos 0-270
  const int servomin = 120;                 // This is the 'minimum' pulse length count (out of 4096)
  const int servomax = 500;                 // This is the 'maximum' pulse length count (out of 4096)
  int pulse = map(degree, 0, 270, servomin, servomax);
  pwm.setPWM(pin, 0, pulse);
}

void TDServoControl(int pin, int degree) {  //control function for TD-8160MG servos 0-255
  const int servomin = 65;                  // This is the 'minimum' pulse length count (out of 4096)
  const int servomax = 500;                 // This is the 'maximum' pulse length count (out of 4096)
  int pulse = map(degree, 0, 255, servomin, servomax);
  pwm.setPWM(pin, 0, pulse);
}

void base(int degree) {
  MGServoControl(8, degree);
}
void shoulder(int degree) {
  TDServoControl(9, degree);
}
void elbow(int degree) {
  DSServoControl(10, 270 - degree);
}
void wrist1(int degree) {
  DSServoControl(11, 270 - degree);
}
void wrist2(int degree) {
  MGServoControl(12, 270 - degree);
}
void wrist3(int degree) {
  MGServoControl(13, 270 - degree);
}

void gripper(bool status) {
  if (status) {
    SGServoControl(14, 70);  //closed
    SGServoControl(15, 70);
  } else {
    SGServoControl(14, 0);  //open
    SGServoControl(15, 0);
  }
}

void upright() {
  //Base - 0
  MGServoControl(8, 0);
  //Shoulder - 1
  TDServoControl(9, 120);
  //Elbow - 2
  DSServoControl(10, 135);
  //Yaw - 3
  DSServoControl(11, 0);
  //Pitch - 4
  MGServoControl(12, 60);
  //Roll - 5
  MGServoControl(13, 90);
}
