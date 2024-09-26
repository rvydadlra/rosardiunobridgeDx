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
  volatile uint8_t left_last = 0;
// Sağ motorun önceki durumu
  volatile uint8_t right_last = 0;
  static const int8_t ENC_STATES_SOL[] = {
    // Önceki (000)
    0,  1,  -1, 0,  -1,  0,  1,  0,   // Yeni (000000 - 000111)
    // Önceki (001)
    -1,  0,  0,  1,  0,  -1,  0,  1,  // Yeni (001000 - 001111)
    // Önceki (010)
    1,  0,  0,  -1,  0,  1,  0,  -1,  // Yeni (010000 - 010111)
    // Önceki (011)
    0,  -1,  1,  0,  -1,  0,  1,  0,  // Yeni (011000 - 011111)
    // Önceki (100)
    0,  1,  0,  -1,  1,  0,  -1,  0,  // Yeni (100000 - 100111)
    // Önceki (101)
    1,  0,  -1,  0,  -1,  0,  1,  0,  // Yeni (101000 - 101111)
    // Önceki (110)
    0,  -1,  1,  0,  1,  0,  -1,  0,  // Yeni (110000 - 110111)
    // Önceki (111)
    0,  0,  0,  0,  0,  0,  0,  0    // Yeni (111000 - 111111)
};  

static const int8_t ENC_STATES_SAG[] = {
    // Önceki (000)
    0,  -1,  1,  0,  1,  0,  -1,  0,   // Yeni (000000 - 000111)
    // Önceki (001)
    1,  0,  0,  -1,  0,  1,  0,  -1,   // Yeni (001000 - 001111)
    // Önceki (010)
    -1,  0,  0,  1,  0,  -1,  0,  1,   // Yeni (010000 - 010111)
    // Önceki (011)
    0,  1,  -1,  0,  1,  0,  -1,  0,   // Yeni (011000 - 011111)
    // Önceki (100)
    0,  -1,  0,  1,  -1,  0,  1,  0,   // Yeni (100000 - 100111)
    // Önceki (101)
    -1,  0,  1,  0,  1,  0,  -1,  0,   // Yeni (101000 - 101111)
    // Önceki (110)
    0,  1,  -1,  0,  -1,  0,  1,  0,   // Yeni (110000 - 110111)
    // Önceki (111)
    0,  0,  0,  0,  0,  0,  0,  0      // Yeni (111000 - 111111)
};
  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  void leftISR() {
    // D2, D3 ve D21'deki Hall sensör sinyallerini oku
    uint8_t hall_signals = (digitalRead(LEFT_PIN_2) << 2) | (digitalRead(LEFT_PIN_3) << 1) | digitalRead(LEFT_PIN_21);

    // Yeni 3 bitlik Hall sensör sinyalleriyle tabloyu güncelle
    left_last <<= 3;
    left_last |= hall_signals;

    // Pozisyonu güncelle
    left_enc_pos += ENC_STATES_SOL[(left_last & 0x3F)];
}


  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
 void rightISR() {
    // D18, D19 ve D20'deki Hall sensör sinyallerini oku
    uint8_t hall_signals = (digitalRead(RIGHT_PIN_18) << 2) | (digitalRead(RIGHT_PIN_19) << 1) | digitalRead(RIGHT_PIN_20);

    // Yeni 3 bitlik Hall sensör sinyalleriyle tabloyu güncelle
    right_last <<= 3;
    right_last |= hall_signals;

    // Pozisyonu güncelle
    right_enc_pos += ENC_STATES_SAG[(right_last & 0x3F)];
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

