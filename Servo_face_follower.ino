// Servo Face Follower Project
// by Davide Caminati <http://caminatidavide.it> 
// This source code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int actual_position = 90;    // variable to store the servo position 

int min_position = 1;        // max server position
int max_position = 170;      // min server position
int movement_speed = 40;     // turn velocity (from 1 to 40)

int _position;


void setup() 
{ 
  myservo.attach(9);        // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);       // initialize serial:
} 
 
 
void loop() 
{ 
  while (Serial.available() > 0) {
    int _p = Serial.parseInt();  // get the position from serial
    // 0 = right
    // 1 = center
    // 2 = left
    switch (_p){
      case 0:
        _position = 180;
        break;
      case 1:
        _position = 90;
        break;
      case 2:
        _position = 1;
        break;
      default:
        _position = 90;
    }
        
        
    if (Serial.read() == '\n') {
      Serial.println("Actual pos " +  String(actual_position) + " ; Targhet pos " + String(_position));
      movement(_position);              // actuate the movement
    }
  }
}


void movement(int targhet_pos)
{
  if (targhet_pos>actual_position){
    for(int pos = actual_position; pos < targhet_pos; pos += 1)  // goes to targhet position
    {                                    // in steps of 1 degree 
      if (pos<=max_position){             // check the limit of the servo
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        actual_position = pos;       // update the current position
        delay(50-movement_speed);                       // waits for the servo to reach the position 
      }
    } 
  }
  if (targhet_pos<actual_position){
    for(int pos = actual_position; pos > targhet_pos; pos -= 1)  // goes to targhet position
    {                                    // in steps of 1 degree 
      if (pos>=min_position){             // check the limit of the servo
        myservo.write(pos);              // tell servo to go to position in variable 'pos' 
        actual_position = pos;       // update the current position
        delay(50-movement_speed);                       // waits for the servo to reach the position 
      }
    } 
  }
}
