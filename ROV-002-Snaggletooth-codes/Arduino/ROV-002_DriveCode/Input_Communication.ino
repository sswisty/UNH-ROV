/* Part of ROV-002 Drive Control                                              */
// This function deals with reading and storing the controller values from the controller

int ReadInValues()
{
  // These commands get the raw values from the C++ code and controller inputs
  Serial.print("r");
  RX = Serial.parseInt();
  RY = Serial.parseInt();
  LX = Serial.parseInt();
  LY = Serial.parseInt();
  RT = Serial.parseInt();
  LT = Serial.parseInt();
  R3 = Serial.parseInt();
  L3 = Serial.parseInt();
  RB = Serial.parseInt();
  LB = Serial.parseInt();
  UpD = Serial.parseInt();
  DownD = Serial.parseInt();
  LeftD = Serial.parseInt();
  RightD = Serial.parseInt();
  A = Serial.parseInt();
  B = Serial.parseInt();
  Y = Serial.parseInt();
  X = Serial.parseInt();
  Start = Serial.parseInt();
  Back = Serial.parseInt();
  Verification = Serial.parseInt();

  if (Verification != 9)
  {
    return -1;            // This Verification helps the communication between C++ and arduino
  }

  else
  {
    Serial.print("q");   // When 'q' is printed the C++ code knows all the data was recieved
  }

  RX = map(RX, -32767, 32767, -150, 150);
  RY = map(RY, -32767, 32767, -150, 150);
  LX = map(LX, -32767, 32767, -150, 150);
  LY = map(LY, -32767, 32767, -150, 150);
  LT = map(LT, 0, 255, 0, 150);
  RT = map(RT, 0, 255, 0, -150);            // This is something to look at... Not sure if I have double
                                            // negative in my other codes.
                                            
  // The Trigger values are mapped into a value of +-100 for motor control
  // To eliminate a small motor value when not pressed I am making +/-15 = 0
  
  if (abs(RX) < 15) { RX = 0; }
  if (abs(RY) < 15) { RY = 0; }
  if (abs(LX) < 15) { LX = 0; }
  if (abs(LY) < 15) { LY = 0; }
  if (abs(LT) < 15) { LT = 0; }
  if (abs(RT) < 15) { RT = 0; }
  
  return 0;
}
