int pins[13] = {0, 1, 2, 3, 4,5,6,7,8,9,10,11,12};     // There should be 13 values for Arduino 1, 12 for Arduino 2 (0 counts)
int sv[13];                                            // This should be 13 (Arduino 1) or 12 (Arduino 2)


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);                                 // Watch the baud rate on the python code too...
  Serial.println("Serial comm starts!");
 }
 
 
// the loop routine runs over and over again forever:
void loop() {
  char command;
  if( Serial.available() )
  {
    command = Serial.read();
    if (command == '!')                                 // The python code sends "!" when it wants to read data
      {
       // read the analog in value:
       for( int i = 0; i < 13; i++ )                    // The 13 (ard1) and 12 (ard2) should allign here
       {                                                // Note: The loop does not reach 'X' in i < 'X'
         sv[i] = analogRead( pins[i] );                 // The loop stops the value before. Remember we added 0 as a pin
       }
       //write the analog reads from the
       //Serial.print("sensor = " );
       for( int i = 0; i < 13; i++ )                    // Again 13 for Arduino 1 and 12 for Arduino 2
       {
         Serial.print(sv[i]);
         Serial.print(" ");                 // This might have to be a ", " for the original python codes to work...
       }
       Serial.print( "\n" );
       // wait 2 milliseconds before the next loop
       // for the analog-to-digital converter to settle
       // after the last reading:
       delay(2);
      } 
   }
}
