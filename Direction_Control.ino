/* Part of ROV-002 Drive Control                                         */
// Incase a motor is required twice Direction Correction accounts for both 
//  commands

int DirectionCorrection(long primaryValue, long secondaryValue, char side)
{
  int correctedValue = 0;
  
  if (side == '+')
  {
    correctedValue = primaryValue/2 + primaryValue*secondaryValue/800;
  }
  
  else if (side == '-')
  {
    correctedValue = primaryValue/2 - primaryValue*secondaryValue/800;
  }
  
  return correctedValue;
}
