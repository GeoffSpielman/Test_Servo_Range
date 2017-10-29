//Created by Geoff Spielman on 2017-10-29
/* HS-5245MG SERVO (camera pitch) website info:  
 *  No load speed at 4.8V: 0.15sec/60°
 *  Max PWM range:  750-2250μsec
 *  Travel per μs: 0.079°/μsec
 *  Max travel: 118°
 *  Pulse Amplitude: 3 - 5 V
 *  Deadband width: 1 μs 
*/

/* HS-1425CR SERVO (camera yaw) website info:  
 *  No load speed at 4.8V: 44 RPM
 *  Pulse Amplitude: 3 - 5 V
 *  Deadband width: 1 μs 
*/


bool testingAngles = false;

const int MAX_ANGLE = 163; //stops moving at 164
const int MIN_ANGLE = 21; //stops moving at 20
const int REST_ANGLE = 92;
const int ANGLE_INCREMENT = 1;
int pitchPos = REST_ANGLE;

const int PITCH_MAX_VALUE = 2230; //stops moving at 2240
const int PITCH_MIN_VALUE = 760; //stops moving at 750
const int PITCH_REST_VALUE = 1375;
const int PITCH_PWM_INCREMENT = 5;
int pitchVal = PITCH_REST_VALUE;


const int YAW_MAX_CCW = 1610; //highest CCW speed
const int YAW_MIN_CCW = 1508; //slowest smooth CCW speed
const int YAW_MAX_CW = 1390; // highest CW speed 
const int YAW_MIN_CW = 1455;//slowest smooth CW speed
const int YAW_REST_VALUE = 1480; //starts CW at 1454, starts CCW at 1506
const int YAW_PWM_INCREMENT = 1;
int yawVal = YAW_REST_VALUE;



#include <Servo.h>
char input[20];
Servo pitchServo;
Servo yawServo;

void setup() {
  Serial.begin(9600);
  Serial.println("---- Start -----");
  pitchServo.attach(9);  // pitch servo should be plugged into pin 9
  yawServo.attach(6);    // yaw servo should be plugged into pin 6
  
  if (testingAngles){
    pitchServo.write(REST_ANGLE);
  }
  else{
    pitchServo.writeMicroseconds(PITCH_REST_VALUE);
  }
  yawServo.writeMicroseconds(YAW_REST_VALUE);
}

void loop() {
  Serial.print("Pitch cur: ");
  Serial.print(testingAngles ? pitchPos: pitchVal);
  Serial.println("\t\t increase: i, decrease: d, highest: h, lowest: l, rest: r");
  Serial.print("Yaw cur: ");
  Serial.print(yawVal);
  Serial.println("\t\t increase: w, decrease: e, top CCW: t, top CW: y \t\t STOP: s");
  Serial.read();

  while (!Serial.available());
  Serial.readString().toCharArray(input, 20);

  if (input[0] == 's' || input[0] == 's'){
    pitchServo.writeMicroseconds(PITCH_REST_VALUE);
    yawServo.writeMicroseconds(YAW_REST_VALUE);
    Serial.println("--- Ending Program ---");
    while(1){};
  }

  if (testingAngles){
    switch (input[0]){
      case 'i':
          pitchPos += ANGLE_INCREMENT;
          break;
      case 'I':
          pitchPos += 3*ANGLE_INCREMENT;
          break;
      case 'd':
          pitchPos -= ANGLE_INCREMENT;
          break;
      case 'D':
          pitchPos -= 3*ANGLE_INCREMENT;
          break;
      
      case 'h':
          pitchPos = MAX_ANGLE;
          break;
     case 'l':
          pitchPos = MIN_ANGLE;
          break;
    case 'r':
          pitchPos = REST_ANGLE;
          break;
    }
    pitchServo.write(pitchPos); 
  }
  else{
    switch (input[0]){
      case 'i':
          pitchVal += PITCH_PWM_INCREMENT;
          break;
      case 'I':
          pitchVal += 3*PITCH_PWM_INCREMENT;
          break;
      case 'd':
          pitchVal -= PITCH_PWM_INCREMENT;
          break;
      case 'D':
          pitchVal -= 3*PITCH_PWM_INCREMENT;
          break;
      case 'h':
          pitchVal = PITCH_MAX_VALUE;
          break;
     case 'l':
          pitchVal = PITCH_MIN_VALUE;
          break;
      case 'r':
          pitchVal = PITCH_REST_VALUE;
          break;
    }
    pitchServo.write(pitchVal); 
  }

  
  switch(input[0]){
    case 'w':
      yawVal += YAW_PWM_INCREMENT;
      break;
    case 'W':
      yawVal += 10 * YAW_PWM_INCREMENT;
      break;
    case 'e':
      yawVal -= YAW_PWM_INCREMENT;
      break;
    case 'E':
      yawVal -= 10 * YAW_PWM_INCREMENT;
      break;
    case 'r':
      yawVal = YAW_REST_VALUE;
      break;
    case 't':
      yawVal = YAW_MAX_CCW;
      break;
    case 'y':
      yawVal = YAW_MAX_CW;
      break;
    
  }
  yawServo.writeMicroseconds(yawVal);
}

