/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
   
#ifdef ARDUINO_ENC_COUNTER
 
#define LEFT_ENC_PIN_A PD2  //pin 2
#define LEFT_ENC_PIN_B PD3  //pin 3
#define LEFT_ENC_PIN_C PD4  //pin 4
  
  //below can be changed, but should be PORTC pins
#define RIGHT_ENC_PIN_A PC4   //pin A4
#define RIGHT_ENC_PIN_B PC5 //pin A5
#define RIGHT_ENC_PIN_C PC6 //pin A6-D31
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

