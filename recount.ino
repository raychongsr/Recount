//-------------------------- LED CODE ---------------------------//

#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 23

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 22
#define CLOCK_PIN 13
#define BUTT1_PIN 2
#define BUTT2_PIN 3
#define BUTT3_PIN 4


#define MGPu CRGB(0x8010ff) 

//ANIMATED1 VARIABLES

//start LED blinks, LEDa0
unsigned long event_a0 = 17000;
//LEDa1
unsigned long event_a1 = 22000;


//LEDaBar
unsigned long event_aBar = 33000;

//LEDa5
unsigned long event_a2 = 76000;

unsigned long endTimeA = 86000; 

//ANIMATED2 VARIABLES

//start LED blinks, LEDb0
unsigned long event_b0 = 14000;
//LEDb1
unsigned long event_b1 = 25000;
//LEDb2
unsigned long event_b2 = 36000;

//LEDbBar
unsigned long event_bBar = 47000;

//LEDb12
unsigned long event_b3 = 150000;

//LEDb13
unsigned long event_b4 = 163000;
//LEDb14
unsigned long event_b5 = 176000;
//LEDb15
unsigned long event_b6 = 189000;
//LEDb16
unsigned long event_b7 = 202000;

unsigned long endTimeB = 217000; 


//ANIMATED3 VARIABLES
//start LED blinks, LEDc0
unsigned long event_c0 = 22000;
//LEDc1
unsigned long event_c1 = 36000;
//LEDc2
unsigned long event_c2 = 50000;

//LEDcBar
unsigned long event_cBar = 65000;
float FastLED_fade_counter = 0;


//LED14
unsigned long event_c3 = 160000;
//LED15
unsigned long event_c4 = 181000;
//LED16
unsigned long event_c5 = 192000;
//LED17
unsigned long event_c6 = 203000;
//LED18
unsigned long event_c7 = 214000;
//LED19
unsigned long event_c8 = 225000;
//LED20
unsigned long event_c9 = 236000;
//LED21
unsigned long event_c10 = 247000;
//LED22
unsigned long event_c11 = 258000;
//LED23
unsigned long event_c12 = 269000;



unsigned long startTime = 0; 
unsigned long endTimeC = 283000; 



int value1 = 0;
int value2 = 0;
int value3 = 0;

//int prevalue1 = 0;
//int prevalue2 = 0;

int state = 0; 



// Define the array of leds
CRGB leds[NUM_LEDS];

//-------------------------- AUDIO CODE ---------------------------//

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playWav1;     //xy=263,553
AudioOutputI2S           i2s1;           //xy=633,710
AudioConnection          patchCord1(playWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=593,849
// GUItool: end automatically generated code

float vol = 0.45;
float timer2 ;

// SD CARD ACCESS
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

//INPUT/OUTPUT PARAMETERS

char sample0[] = "RAY3.WAV";  // replace this with the name of the WAV file you want to play from the SD card
char sample1[] = "RAY1.WAV";  // replace this with the name of the WAV file you want to play from the SD card
char sample2[] = "RAY2.WAV";  // replace this with the name of the WAV file you want to play from the SD card
char *currentSample;  

//-------------------------- SETUP ---------------------------//
void setup() {
  
  Serial.begin(9600); //serial communication between the teensy and the computer
  Serial.println("Device starting up");

   // ----- LED & BUTTON Setup ---//


      pinMode(BUTT1_PIN, INPUT_PULLDOWN);
      pinMode(BUTT2_PIN, INPUT_PULLDOWN);
      pinMode(BUTT3_PIN, INPUT_PULLDOWN);

  	  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  
   // ----- Audio Setup ---//
      // Audio connections require memory to work.  For more detailed information, see the MemoryAndCpuUsage example
     AudioMemory(8);
     sgtl5000_1.enable();
     sgtl5000_1.volume(vol);
     SPI.setMOSI(SDCARD_MOSI_PIN);
      SPI.setSCK(SDCARD_SCK_PIN);
    if (!(SD.begin(SDCARD_CS_PIN))) {
      // stop here, but print a message repetitively
      while (1) {
        Serial.println("Unable to access the SD card");
        delay(500);
      }
    }else{
       Serial.println("SD card found");
    }
    Serial.println("Device ready");

    timer2 = (event_c3-event_cBar)/255;
    Serial.println(timer2);

}


// ------------------------------- MAIN LOOP --------------------------------- //
void loop() {

  /*------ INPUT READING (SENSOR READINGS)-----*/
 
  //Serial.println(vol);

  value1 = digitalRead(BUTT1_PIN);
  value2 = digitalRead(BUTT2_PIN);
  value3 = digitalRead(BUTT3_PIN);


  if (value1 == 1) {
    startTime = millis();
    state = 1;
  }
  else if (value2 ==1) {
    startTime = millis();
    state = 2;
  }
    else if (value3 ==1) {
    startTime = millis();
    state = 3;
  }



   
  /*----- OUTPUT LOGIC -----*/
  
  if (state == 0){
    //off();
    standBy();
  }
  else if (state == 1){
    playFile(sample0);
    animated3();
  }
  else if (state == 2){
    playFile(sample2);
    animated2();
  }
    else if (state == 3){
    playFile(sample1);
    animated1();
  }
  //audioTest(); // Plays the audio sample
}

// ------------------------- LED FUNCTIONS ---------------------------------- //

void standBy(){
    // draw a generic, no-name rainbow
  static uint8_t starthue = 0;

  FastLED.setBrightness( 50 );
  fill_rainbow( leds, NUM_LEDS, --starthue, 10);
  FastLED.show();
  FastLED.delay(8);
  
}

//Animation for RAY1

void animated1() {
  FastLED.setBrightness( 255 );
 if ( millis() - startTime < event_a0 ) {
   off();
 }

  //1st part of audio

  else if ( millis() - startTime > event_a0 &&  millis() - startTime < event_aBar) {
  // Turn the LED on, then pause
  leds[0] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[0] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }


  //2nd part of audio, for LED bar

   else if ( millis() - startTime > event_aBar && millis() - startTime < event_a2) {
       for ( int i = 0; i < 1; i++ ){
         leds[i] = CRGB::DarkRed; // Can be any colour
       }

        for ( int i = 1; i < 5; i++ )
          {
            leds[i] = CRGB::Yellow; // Can be any colour
            leds[i].maximizeBrightness(FastLED_fade_counter);  // 'FastLED_fade_counter' How high we want to fade up to 255 = maximum.
          }
            FastLED.show();
            if(FastLED_fade_counter<255){
              FastLED_fade_counter ++;   // Increment
            }
            delay(timer2);
  }
  
  else if ( millis() - startTime > event_a2) {
    for ( int i = 0; i < 1; i++ ){
    // Turn the LED on, then pause
    leds[i] = CRGB::CornflowerBlue ;
    FastLED.show();
    delay(100);
    // Now turn the LED off, then pause
    leds[i] = CRGB::PowderBlue;
    FastLED.show();  
      delay(100);
    }
  }


  

   //For LED 5

    if ( millis() - startTime > event_a2 ) {
  // Turn the LED on, then pause
  leds[5] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[5] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[7] = CRGB::Black;
  //FastLED.show();  
  }




if ( millis() - startTime > endTimeA) {
  startTime = millis();
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  leds[3] = CRGB::Black;
  leds[4] = CRGB::Black;
  leds[5] = CRGB::Black;

  leds[6] = CRGB::Black;
  leds[7] = CRGB::Black;
  leds[8] = CRGB::Black;
  leds[9] = CRGB::Black;
  leds[10] = CRGB::Black;
  leds[11] = CRGB::Black;
  leds[12] = CRGB::Black;
  leds[13] = CRGB::Black;
  leds[14] = CRGB::Black;
  leds[15] = CRGB::Black;
  leds[16] = CRGB::Black;
  leds[17] = CRGB::Black;
  leds[18] = CRGB::Black;
  leds[19] = CRGB::Black;
  leds[20] = CRGB::Black;
  leds[21] = CRGB::Black;
  leds[22] = CRGB::Black;

  FastLED.show();  
  state =0;
  
}


}

//Animation for RAY2

void animated2() {
  FastLED.setBrightness( 255 );
 if ( millis() - startTime < event_b0 ) {
   off();
 }

 if ( millis() - startTime > event_b0 &&  millis() - startTime < event_bBar) {
  // Turn the LED on, then pause
  leds[0] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[0] = CRGB::PowderBlue;
  FastLED.show();  
  delay(100);

  }




//For LED 1

 if ( millis() - startTime > event_b1 &&  millis() - startTime < event_bBar) {
  // Turn the LED on, then pause
  leds[1] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[1] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }


//For LED 2

  if ( millis() - startTime > event_b2 &&  millis() - startTime < event_bBar ) {
  // Turn the LED on, then pause
  leds[2] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[2] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }




//For LED bar

  if ( millis() - startTime > event_bBar && millis() - startTime < event_b3) {
       for ( int i = 0; i < 3; i++ ){
         leds[i] = CRGB::DarkRed; // Can be any colour
       }

    
      for ( int i = 3; i < 12; i++ )
          {
            leds[i] = CRGB::Yellow; // Can be any colour
            leds[i].maximizeBrightness(FastLED_fade_counter);  // 'FastLED_fade_counter' How high we want to fade up to 255 = maximum.
          }
            FastLED.show();
            if(FastLED_fade_counter<255){
              FastLED_fade_counter ++;   // Increment
            }
            
            delay(timer2);
  }

  if ( millis() - startTime > event_b3) {
    for ( int i = 0; i < 3; i++ ){
    // Turn the LED on, then pause
    leds[i] = CRGB::CornflowerBlue ;
    FastLED.show();
    delay(100);
    // Now turn the LED off, then pause
    leds[i] = CRGB::PowderBlue;
    FastLED.show();  
      delay(100);
    }


   //For LED 12
      // Turn the LED on, then pause
  leds[12] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[12] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }


     //For LED 13

  if ( millis() - startTime > event_b4 ) {
  // Turn the LED on, then pause
  leds[13] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[13] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }


     //For LED 14

  if ( millis() - startTime > event_b5 ) {
  // Turn the LED on, then pause
  leds[14] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[14] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }


     //For LED 15

  if ( millis() - startTime > event_b6 ) {
  // Turn the LED on, then pause
  leds[15] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[15] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }


       //For LED 16

  if ( millis() - startTime > event_b7 ) {
  // Turn the LED on, then pause
  leds[16] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[16] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }


if ( millis() - startTime > endTimeB) {
  startTime = millis();
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  leds[3] = CRGB::Black;
  leds[4] = CRGB::Black;
  leds[5] = CRGB::Black;

  leds[6] = CRGB::Black;
  leds[7] = CRGB::Black;
  leds[8] = CRGB::Black;
  leds[9] = CRGB::Black;
  leds[10] = CRGB::Black;
  leds[11] = CRGB::Black;
  leds[12] = CRGB::Black;
  leds[13] = CRGB::Black;
  leds[14] = CRGB::Black;
  leds[15] = CRGB::Black;
  leds[16] = CRGB::Black;
  leds[17] = CRGB::Black;
  leds[18] = CRGB::Black;
  leds[19] = CRGB::Black;
  leds[20] = CRGB::Black;
  leds[21] = CRGB::Black;
  leds[22] = CRGB::Black;

  FastLED.show();  
  state =0;
  
}


}

//Animation for RAY3

void animated3() {
  FastLED.setBrightness( 255 );
 if ( millis() - startTime < event_c0 ) {
   off();
 }

    if ( millis() - startTime > event_c0 &&  millis() - startTime < event_cBar) {
  // Turn the LED on, then pause
  leds[0] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[0] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);

  }




//For LED 1

    if ( millis() - startTime > event_c1 &&  millis() - startTime < event_cBar) {
  // Turn the LED on, then pause
  leds[1] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[1] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }


//For LED 2

    if ( millis() - startTime > event_c2 &&  millis() - startTime < event_cBar ) {
  // Turn the LED on, then pause
  leds[2] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[2] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }


//For LED bar

    if ( millis() - startTime > event_cBar && millis() - startTime < event_c3) {
       for ( int i = 0; i < 4; i++ ){
         leds[i] = CRGB::DarkRed; // Can be any colour
       }

    
      for ( int i = 3; i < 13; i++ )
          {
            leds[i] = CRGB::Yellow; // Can be any colour
            leds[i].maximizeBrightness(FastLED_fade_counter);  // 'FastLED_fade_counter' How high we want to fade up to 255 = maximum.
          }
            FastLED.show();
            if(FastLED_fade_counter<255){
              FastLED_fade_counter ++;   // Increment
            }
            delay(timer2);
  }
  else if ( millis() - startTime > event_c3) {
    for ( int i = 0; i < 3; i++ ){
    // Turn the LED on, then pause
    leds[i] = CRGB::CornflowerBlue ;
    FastLED.show();
    delay(100);
    // Now turn the LED off, then pause
    leds[i] = CRGB::PowderBlue;
    FastLED.show();  
      delay(100);
    }
  }



//For LED 13

    if ( millis() - startTime > event_c3 ) {
  // Turn the LED on, then pause
  leds[13] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[13] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[6] = CRGB::Black;
  //FastLED.show();  
  }
  
  //For LED 14

    if ( millis() - startTime > event_c4 ) {
  // Turn the LED on, then pause
  leds[14] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[14] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[7] = CRGB::Black;
  //FastLED.show();  
  }

   //For LED 15

    if ( millis() - startTime > event_c5 ) {
  // Turn the LED on, then pause
  leds[15] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[15] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[7] = CRGB::Black;
  //FastLED.show();  
  }

     //For LED 16

    if ( millis() - startTime > event_c6 ) {
  // Turn the LED on, then pause
  leds[16] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[16] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[7] = CRGB::Black;
  //FastLED.show();  
  }

     //For LED 17

    if ( millis() - startTime > event_c7 ) {
  // Turn the LED on, then pause
  leds[17] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[17] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[7] = CRGB::Black;
  //FastLED.show();  
  }

     //For LED 18

    if ( millis() - startTime > event_c8 ) {
  // Turn the LED on, then pause
  leds[18] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[18] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[7] = CRGB::Black;
  //FastLED.show();  
  }

     //For LED 29

    if ( millis() - startTime > event_c9 ) {
  // Turn the LED on, then pause
  leds[19] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[19] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[7] = CRGB::Black;
  //FastLED.show();  
  }

     //For LED 20

    if ( millis() - startTime > event_c10 ) {
  // Turn the LED on, then pause
  leds[20] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[20] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[7] = CRGB::Black;
  //FastLED.show();  
  }

     //For LED 21

    if ( millis() - startTime > event_c11 ) {
  // Turn the LED on, then pause
  leds[21] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[21] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[7] = CRGB::Black;
  //FastLED.show();  
  }

     //For LED 22

    if ( millis() - startTime > event_c12 ) {
  // Turn the LED on, then pause
  leds[22] = CRGB::CornflowerBlue ;
  FastLED.show();
  delay(100);
  // Now turn the LED off, then pause
  leds[22] = CRGB::PowderBlue;
  FastLED.show();  
    delay(100);
  }
  else {
  //leds[7] = CRGB::Black;
  //FastLED.show();  
  }

if ( millis() - startTime > endTimeC) {
  startTime = millis();
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  leds[3] = CRGB::Black;
  leds[4] = CRGB::Black;
  leds[5] = CRGB::Black;

  leds[6] = CRGB::Black;
  leds[7] = CRGB::Black;
  leds[8] = CRGB::Black;
  leds[9] = CRGB::Black;
  leds[10] = CRGB::Black;
  leds[11] = CRGB::Black;
  leds[12] = CRGB::Black;
  leds[13] = CRGB::Black;
  leds[14] = CRGB::Black;
  leds[15] = CRGB::Black;
  leds[16] = CRGB::Black;
  leds[17] = CRGB::Black;
  leds[18] = CRGB::Black;
  leds[19] = CRGB::Black;
  leds[20] = CRGB::Black;
  leds[21] = CRGB::Black;
  leds[22] = CRGB::Black;

  FastLED.show();  
  state =0;
  
}


}

void off(){
  for (int i = 0; i< NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  delay(4000);
  FastLED.show();  
}

// ------------------------- AUDIO FUNCTIONS ---------------------------------- //
void playFile(const char *filename)
{
  // Start playing the file if it's not already playing
  if(!playWav1.isPlaying() || (playWav1.isPlaying() &&  currentSample != filename) ) {
    Serial.print("Playing file: ");
    Serial.println(filename);
    playWav1.play(filename);
    currentSample = filename;
  }
  // A brief delay for the library read WAV info
  delay(25);
}

void stopFile(const char *filename)
{
  if(playWav1.isPlaying()){
   Serial.print("Stop playback file: ");
   Serial.println(filename);
    playWav1.stop();
  }
  // A brief delay for the library read WAV info
  delay(25);
}


// ------------------------- BEHAVIOURS ---------------------------------- //
//TESTER FUNCTION NOT USED ATM
void audioTest(){
  playFile(sample0);  // filenames are always uppercase 8.3 format
}