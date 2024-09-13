/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef BLDC_DRIVER 

#define DIR_PINR 9   // Yön kontrol pini                        
#define PWM_PINR 5 // Hız kontrolü için PWM pini
#define DIR_PINL 10  // Yön kontrol pini                       

#define PWM_PINL 6 // Hız kontrolü için PWM pini

#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
