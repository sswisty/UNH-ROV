/* Part of ROV-002 Drive Control                                        */

void Initialize()
{
  
  pinMode(T1pwm, OUTPUT);
  pinMode(T1dir, OUTPUT);
  pinMode(T2pwm, OUTPUT);
  pinMode(T2dir, OUTPUT);
  pinMode(T3pwm, OUTPUT);
  pinMode(T3dir, OUTPUT);
  pinMode(T4pwm, OUTPUT);
  pinMode(T4dir, OUTPUT);
  pinMode(T5pwm, OUTPUT);
  pinMode(T5dir, OUTPUT);
  pinMode(T6pwm, OUTPUT);
  pinMode(T6dir, OUTPUT); 
  
  pinMode(system_good, OUTPUT);
  pinMode(system_bad, OUTPUT);
  
  // The H-Bridges need to get a direction (HIGH or LOW) and a speed (PWM value from 0-255)
  // To get a forward direction: digitalWrite(T#dir, HIGH)
  // To get a backward direction: digitalWrite(T#dir, LOW)
  // The speed of the thruster is determined from the PWM value (must be positive)
  // This PWM value is read from a controler. The code is analogWrite(T#pwm,RX/RY/LX/LY/RT/LT)
 
 
  delay(1500); 
}
