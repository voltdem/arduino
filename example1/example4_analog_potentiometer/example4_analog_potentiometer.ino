#define analogPort 0
#define ledPortBlue 3
#define ledPortRed 5
#define ledPortGreen 6
int powerGreen, powerRed, powerBlue;
int speedGreen, speedRed, speedBlue;
int valGreen, valRed, valBlue;
unsigned long timer1 = 0, timer2 = 0, timer3 = 0;
int const minPwr = 0;
int const maxPwr = 10000;

void setup() {
  Serial.begin(9600);
  speedGreen = random( 1, 5 );
  speedBlue =  random( 1, 5 );
  speedRed =  random( 1, 5 );
  valGreen = 0; 
  valRed = 0;
  valBlue = 0;
  powerGreen = 0;
  powerRed = 0;
  powerBlue = 0;
}

void loop() {
  int posit;
  if ( millis( ) - timer1 > 10 ){
    timer1 = millis( );
    posit = analogRead(analogPort);
    posit = map( posit, 0, 1023, 0, 20 );
    //Serial.println( powerBlue );
  }
  if ( millis( ) - timer3 > 10000 ){
    timer3 = millis( );
    speedGreen = random( 1, 5 );
    speedBlue =  random( 1, 5 );
    speedRed =  random( 1, 5 );
  }
  if ( millis( ) - timer2 > 100 ){
    timer2 = millis( );
    addVal( valGreen, speedGreen, posit );
    addVal( valRed, speedRed, posit );
    addVal( valBlue, speedBlue, posit  );
    mapPwr( valGreen, powerGreen );
    mapPwr( valRed, powerRed );
    mapPwr( valBlue, powerBlue );
    analogWrite(ledPortBlue, powerBlue);
    analogWrite(ledPortGreen, powerGreen);
    analogWrite(ledPortRed, powerRed);

  }
}

void addVal(int& curPwr, int& speedV, int posit){
  int curSpeed = speedV * posit;
  if ( curPwr + curSpeed <= minPwr ){
    curPwr = minPwr;
    speedV = - speedV;
    return;
  }
  if ( curPwr + curSpeed >= maxPwr ){
    curPwr = maxPwr;
    speedV = - speedV;
    return;
  }  
  curPwr += curSpeed;
}

void mapPwr( int& curPwr, int& powerV ){
  powerV = map( curPwr, minPwr, maxPwr, 0, 255 );
  powerV = constrain( powerV, 0, 255 );
}
