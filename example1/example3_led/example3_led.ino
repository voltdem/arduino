#include "OneButton.h"
int const pinLed = 8;
OneButton button1( 2, true );
unsigned long lastPress = 0;
boolean ledState = false;

void setup() {
  // put your setup code here, to run once:
  pinMode( pinLed, OUTPUT );
  button1.attachClick( click1 );
  Serial.begin(9600);
}

void loop() {
  if ( millis( ) - lastPress > 10 ){
    button1.tick( );
    lastPress = millis( );
  }
  // put your main code here, to run repeatedly:

}

void click1( ){
  Serial.println( "Button is pressed");
  ledState = !ledState;
  Serial.print( "LED state:"); 
  Serial.println( ledState );
  digitalWrite( pinLed, ledState );
}
