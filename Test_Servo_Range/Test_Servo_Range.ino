
/* HS-5245MG SERVO (camera pitch):  
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

bool testingAngles = true;

const int MAX_ANGLE = 163; //stops moving at 164
const int MIN_ANGLE = 21; //stops moving at 20
const int REST_ANGLE = 92;
const int ANGLE_INCREMENT = 1;

const int LED = 13;
 
#include <Servo.h>

Servo pitchServo;  // create servo object to control a servo
int pitchPos = REST_ANGLE;    // servo position
char input[20];

void setup() {
  Serial.begin(9600);
  Serial.println("---- Start -----");
  pinMode(13, OUTPUT); //LED onboard
  pitchServo.attach(9);  // attaches the servo on pin 9 to the servo object
  pitchServo.write(REST_ANGLE);
}


void loop() {
  Serial.print("cur: ");
  Serial.print(pitchPos);
  Serial.println(". Jump to max (h), increase (i), decrease (d), jump to min (l), rest posiion (r), or stop (s)?");
  Serial.read();

  while (!Serial.available());
  Serial.readString().toCharArray(input, 20);

  switch (input[0]){
    case 'i':
        pitchPos += ANGLE_INCREMENT;
        pitchServo.write(pitchPos); 
        break;
    case 'd':
        pitchPos -= ANGLE_INCREMENT;
        pitchServo.write(pitchPos); 
        break;
    case 's':
        Serial.println("--- Ending Program ---");
        while(1){};
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
  }
}

void blinkLED(int times){
  for (int i = 0; i < times; i ++){
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(200);              // wait for a second
  }
  return;
}

