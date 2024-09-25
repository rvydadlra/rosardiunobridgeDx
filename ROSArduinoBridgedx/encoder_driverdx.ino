/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#ifdef ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }
#elif defined(ARDUINO_ENC_COUNTER)
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
 static const int8_t HALL_STATES[] = {0, 1, -1, 0, -1, 0, 0, 1};    
  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  
ISR(PCINT2_vect) {
    static uint8_t hall_last = 0; // Önceki Hall durumu saklanır

    hall_last <<= 3; // Önceki durumu üç bit sola kaydır
    hall_last |= (PIND & (7 << 2)) >> 2;  // D2, D3, D4'teki HallA, HallB, HallC sinyallerini oku

    // Sol motorun pozisyonunu güncelle
    left_motor_pos += HALL_STATES[hall_last & 0x07]; // Tabloyu kullanarak pozisyonu güncelle
}

  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  ISR (PCINT1_vect){
        static uint8_t hall_last = 0;
          	
	hall_last <<= 3; // Önceki durumu üç bit sola kaydır
	hall_last |= (PINC & (7 << 4)) >> 4;  // C4, C5, C6'teki HallA, HallB, HallC sinyallerini oku
  
  	 right_motor_pos += HALL_STATES[hall_last & 0x07];  // Hall sinyallerine göre pozisyonu güncelle
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif

