/* HS-5245MG SERVO (camera pitch) website info:  
 *  No load speed at 4.8V: 0.15sec/60°
 *  Max PWM range:  750-2250μsec
 *  Travel per μs: 0.079°/μsec
 *  Max travel: 118°
 *  Pulse Amplitude: 3 - 5 V
 *  Deadband width: 1 μs 
*/

/* for writeMicroseconds, on standard servos: 
 *    1000 is fully counter-clockwise
 *    2000 is fully clockwise
 *    1500 is in the middle.
 */

bool testingAngles = false;

const int MAX_ANGLE = 163; //stops moving at 164
const int MIN_ANGLE = 21; //stops moving at 20
const int REST_ANGLE = 92;
const int ANGLE_INCREMENT = 1;
int pitchPos = REST_ANGLE;

const int MAX_VALUE = 2230; //stops moving at 2240
const int MIN_VALUE = 760; //stops moving at 750
const int REST_VALUE = 1495;
const int PWM_INCREMENT = 5;
int curVal = REST_VALUE;


#include <Servo.h>
char input[20];
Servo pitchServo;

void setup() {
  Serial.begin(9600);
  Serial.println("---- Start -----");
  pitchServo.attach(9);  // servo should be plugged into pin 9
  
  if (testingAngles){
    pitchServo.write(REST_ANGLE);
  }
  else{
    pitchServo.writeMicroseconds(REST_VALUE);
  }
}

void loop() {
  Serial.print("cur: ");
  Serial.print(testingAngles ? pitchPos: curVal);
  Serial.println(". Jump to max (h), increase (i), decrease (d), jump to min (l), rest posiion (r), or stop (s)?");
  Serial.read();

  while (!Serial.available());
  Serial.readString().toCharArray(input, 20);

  if (testingAngles){
    switch (input[0]){
      case 'i':
          pitchPos += ANGLE_INCREMENT;
          pitchServo.write(pitchPos); 
          break;
      case 'I':
          pitchPos += 3*ANGLE_INCREMENT;
          pitchServo.write(pitchPos); 
          break;
      case 'd':
          pitchPos -= ANGLE_INCREMENT;
          pitchServo.write(pitchPos); 
          break;
      case 'D':
          pitchPos -= 3*ANGLE_INCREMENT;
          pitchServo.write(pitchPos); 
          break;
      
      case 'h':
          pitchPos = MAX_ANGLE;
          pitchServo.write(pitchPos); 
          break;
     case 'l':
          pitchPos = MIN_ANGLE;
          pitchServo.write(pitchPos); 
          break;
    case 'r':
          pitchPos = REST_ANGLE;
          pitchServo.write(pitchPos); 
          break;
    case 's':
          Serial.println("--- Ending Program ---");
          while(1){};
          break;
    }
  }
  else{
    switch (input[0]){
      case 'i':
          curVal += PWM_INCREMENT;
          pitchServo.write(curVal); 
          break;
      case 'I':
          curVal += 3*PWM_INCREMENT;
          pitchServo.write(curVal); 
          break;
      case 'd':
          curVal -= PWM_INCREMENT;
          pitchServo.write(curVal); 
          break;
      case 'D':
          curVal -= 3*PWM_INCREMENT;
          pitchServo.write(curVal); 
          break;
      case 'h':
          curVal = MAX_VALUE;
          pitchServo.write(curVal); 
          break;
     case 'l':
          curVal = MIN_VALUE;
          pitchServo.write(curVal); 
          break;
    case 'r':
          curVal = REST_VALUE;
          pitchServo.write(curVal); 
          break;
     case 's':
          Serial.println("--- Ending Program ---");
          while(1){};
          break;
    }
  }
}

