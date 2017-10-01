# Test_Servo_Range
Allows the user to find the max and min angles of their digital servo using the Serial Monitor on an Arduino. 
Supports angular positions and microsecond control over PWM for finer resolution.

Connect servo signal pin (typically yellow) to pin 9.

Set the boolean at the top for either angular testing (true) or microsecond testing directly (false).

- i = increment current angle by ANGLE_INCREMENT or current value by PWM_INCREMENT
- d = decrement current angle by ANGLE_INCREMENT or current value by PWM_INCREMENT
- h = go to the highest value you're testing for (MAX_ANGLE or MAX_VALUE)
- l = go to the lowest value you're testing for (MIN_ANGLE or MIN_VALUE)
- r = go to a rest position, set by REST_ANGLE or REST_VALUE. Useful prior to ending the program
- s = stop testing (just enters infinite loop)
