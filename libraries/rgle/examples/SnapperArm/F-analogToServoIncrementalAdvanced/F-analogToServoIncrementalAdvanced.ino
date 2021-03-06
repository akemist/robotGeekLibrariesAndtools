/***********************************************************************************
 *   ___________
 *  |     __    |           RG 101 - Servo 
 *  |   /    \  |                Analog To Servo - Incremental
 *  |  |      | |
 *  |   \ __ /  |
 *  |           |
 *  |           |
 *  |___________|     
 *  
 *  This code is intended for use with the RobotGeek Snapper Arm and the RobotGeek
 *   curriculum.
 *  
 *  This code will set the positions on a servo using servo.write()
 *  based on the input from an analog sensor. It will use the analog input from the third 
 *  joystick (analog pin 3) and target the wrist servo on the arm (digital pin 9).
 *  
 *  This code will take into account the physical properties of a joystick by incrementally
 *  adjusting the servo. This means that when the joystick is centered, the servo will stay
 *  at its current positon. When the servo is moved, it will adjust the servos postion slowly.
 *  
 *  Digital 9 - RobotGeek Servo
 *  Analog 3 - RobotGeek Rotation Knob or other Analog Input
 *  
 * For a more in depth explanation of wiring,  this code and more information, see
 * http://learn.robotgeek.com/rgc/262-rgc-robotgeek-snapper-arm.html
 *  
 *  
 * Important Functions
 *  analogRead()
 *  servo.write()
 *  map()
 *****************************************************************************************/

#include <Servo.h>

const int ANALOG_PIN = 0;           //joystick sensor
const int SERVO_PIN = 9;            //pin number for the led pin - this is 'const' since it will not change during code, and saves Arduino memory
const int SERVO_MIN_DEGREE = 0;     //minimum servo positon
const int SERVO_MAX_DEGREE = 180;   //maximum servo position


//deadband values for the joysticks - values between DEADBANDLOW and DEADBANDHIGH will be ignored
const int DEADBANDLOW = 480;   //lower deadband value for the joysticks. Inputs below this value will be used
const int DEADBANDHIGH = 540;  //upper deadband value for the joysticks. Inputs above this value will be used

int analogSensorValue;  //the raw value read from the analog sensor
int servoIncrement;          //the increment to change the servo positon by, derived from the analogSensorValue
int servoValue;           //holds the servo position (0-180)
int maxServoIncrement = 10;         //alter this value to change the speed of the system. Higher values mean higher speeds 5-500 approximate recommended range

Servo wristServo;             //create an instance of the servo class, 'wristServo'

//setup runs once when the Geekduino/Arduino is turned on
void setup()
{
  wristServo.attach(SERVO_PIN); //attach the servo on pin SERVO_PIN
} //setup() is done, go to loop()

//loop runs forever once setup is complete
void loop()
{
  analogSensorValue = analogRead(ANALOG_PIN);   //read the analog sensor and store it in 'analogSensorValue' 

   //check that the joystick is outisde of the deadband (i.e. if the analogSensorValue is less than DEADBANDLOW or snalogSensorValue is greater than DEADBANDHIGH) Movements in the deadband should not register
   if(analogSensorValue < DEADBANDLOW || analogSensorValue > DEADBANDHIGH)
   {
     //analogSensorValue will hold a value between 0 and 1023 that correspods to the location of the joystick. The map() function will convert this value
     //into a value between speed and -speed. 

     servoIncrement = map(analogSensorValue, 0, 1023, -1*maxServoIncrement, maxServoIncrement) ;
     
     servoValue = servoValue + servoIncrement; //add the increment to servoValue to slowly increment/decrement the tiltValue
     
     // We need to keep the servo value between SERVO_MIN_DEGREE and SERVO_MAX_DEGREE. If values go above SERVO_MAX_DEGREE or below SERVO_MIN_DEGREE we will have eratic behavior.
     // the contstrain function takes care of this. Values below SERVO_MIN_DEGREE are set to SERVO_MIN_DEGREE and above SERVO_MAX_DEGREE are set to SERVO_MAX_DEGREE 
     servoValue = constrain(servoValue, SERVO_MIN_DEGREE, SERVO_MAX_DEGREE);	//
   }   

   wristServo.write(servoValue);  //send the servo to the value in 'servoValue', thus adjusting the servo based on the analog input
   delay(10);  //short delay to account for servo movement

  
}//go back to the first line in loop()
