/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
   
#ifdef ARDUINO_ENC_COUNTER
 
#define LEFT_ENC_PIN_A 2  //pin 2
#define LEFT_ENC_PIN_B 3  //pin 3
#define LEFT_ENC_PIN_C 21  //pin 4
  
  //below can be changed, but should be PORTC pins
#define RIGHT_ENC_PIN_A 18   //pin A4
#define RIGHT_ENC_PIN_B 19 //pin A5
#define RIGHT_ENC_PIN_C 20 //pin A6-D31
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

