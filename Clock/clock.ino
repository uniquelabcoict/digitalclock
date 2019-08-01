
//Pin connected to ST_CP of 74HC595
int latchPin = 8;
int latchPin2 = 6;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
int clockPin2 = 7;
////Pin connected to DS of 74HC595
int dataPin = 11;
//blinking lights
int dataPin2 = 10;

int numbers [] = {
  63,48,91,121,116,109,111,56,255,125
};

int hoursLow [] = {
  63,48,91,121,116,109,111,56,255,125,63,48,91
};
int hoursHigh [] = {
  63, 48
};

int amPm = 0;
int amPmPin = 9;


void setup() {
  //Start Serial for debuging purposes  
  Serial.begin(9600);
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(latchPin2, OUTPUT);

}


void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

//internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(amPmPin, OUTPUT);

//clear everything out just in case to
//prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);
 //0001 0100
 //dataout & 1<<
    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}


void loop(){
//    digitalWrite(latchPin, 0);
//        shiftOut(dataPin,clockPin, 121);
//        shiftOut(dataPin,clockPin, 56);
//        digitalWrite(latchPin, 1); 
//        digitalWrite(latchPin2, 0);
//        shiftOut(dataPin2, clockPin2, 125);
//        shiftOut(dataPin2, clockPin2, 48);
//        digitalWrite(latchPin2, 1);
   for(int l=0; l<2; l++){
      for (int g=0;g<10;g++){
         if ((l==0)&&(g==0)){
          continue;
         }
         if((l==1)&&(g==2)){
          amPm = 1-amPm;
         }
         if ((l==1)&&(g==3)){
          break;
         }
        for(int k=0;k<6;k++){
        for(int j=0; j<10; j++){
        for(int z=0; z<60; z++){
        digitalWrite(latchPin, 0);
        shiftOut(dataPin,clockPin, numbers[k]);
        shiftOut(dataPin,clockPin, numbers[j]);
        digitalWrite(latchPin, 1); 
        digitalWrite(latchPin2, 0);
        shiftOut(dataPin2, clockPin2, hoursHigh[l]);
        shiftOut(dataPin2, clockPin2, hoursLow[g]);
        digitalWrite(latchPin2, 1);
        digitalWrite(amPmPin, amPm);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1);
                 }
             }    
         }
      }
   }
}
