/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
   
#ifdef ARDUINO_ENC_COUNTER
 
#define LEFT_ENC_PIN_A PD2  //pin 2
#define LEFT_ENC_PIN_B PD3  //pin 2
#define LEFT_ENC_PIN_C PD4  //pin 2
  
  //below can be changed, but should be PORTC pins
#define RIGHT_ENC_PIN_A PC14   //pin A5
#define LEFT_ENC_PIN_B PC15 //pin 2
#define LEFT_ENC_PIN_C PC16  //pin 2
#endif
   
long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();

