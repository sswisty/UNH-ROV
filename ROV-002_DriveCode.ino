/* ROV 2 Drive Code
   The basic control for an underwater ROV.
   There are six thrusters controlled by controller input.
   The speed of the thrusters corresponds to the joystick movement.
   The ROV has 5 degrees of motion; X, Y, and Z-translation and yaw and pitch
   movements. There is no roll control as that would disorient the video feed.
   
   There is no feedback control (pith, depth, etc) implemented in the Basic
   Drive code.
   
   The basic ROV code has been modified for use with ROV-002 and H-bridges
   
   ROV-002 Drive Control by;
     Shawn Swist
*/

//                             GLOBAL VARIABLES 
//******************************************************************************
#include <Wire.h>

// The six thrusters are controlled through H-bridges that require a direction
// (dir) and a duty cycle speed (pwm).

// Thruster 1 (Back Left)
int T1pwm = 2;  // Pin 1 belongs to communication with computer (TX0 pin)...
int T1dir = 31;

// Thruster 2 (Back Right)
int T2pwm = 3;
int T2dir = 32;   

// Thruster 3 (Side Left)
int T3pwm = 4;
int T3dir = 33;  

// Thruster 4 (Side Right)
int T4pwm = 5;
int T4dir = 34;  

// Thruster 5 (Top Front)
int T5pwm = 6;
int T5dir = 35;  

// Thruster 6 (Top Rear)
int T6pwm = 7;
int T6dir = 36; 

// The System Check Lights
int system_good = 53; // Green light
int system_bad = 52;  // Red light

// Raw values from the controller stored into these variables:
int RT, LT, R3, L3, RB, LB, UpD, DownD, LeftD, RightD, A, B, X, Y, Start, Back, Verification;
int RBPrevState = 0;
long RX, RY, LX, LY;



//                           ARDUINO MAIN LOOP
//*****************************************************************************

void setup() {
  // put your setup code here, to run once:
  
  Initialize();
  
  Serial.begin(115200, SERIAL_8N1);    // Baud here must match baud on C++ code
  
  Serial.setTimeout(100);

}


void loop() 
{
  //int i = 0;
  
  if (Serial.available() > 0)    // XInput Communication loop
  {
    if (ReadInValues() != -1)
      {
        moveROV();
      }
      else
      {
        stopROV();         // The ROV won't move unless it can read values in
      }
      
      digitalWrite(system_good, HIGH);
      digitalWrite(system_bad, LOW);
  }
  
  else
  {
    digitalWrite(system_good, LOW);
    digitalWrite(system_bad, HIGH);
  }

}


  
  
  
