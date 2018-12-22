const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
boolean flag = 0;
boolean ledState = 0;
boolean buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = !digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if ( buttonState == HIGH && flag == false ) {
    // turn LED on:
    Serial.println("Button is pressed");
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    flag = true;
  } 
  if ( buttonState == LOW && flag == true ){
    // turn LED off:
    Serial.println("Button is released");
    flag = false;
  }
}
