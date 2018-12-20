#include <SoftwareSerial.h>
#include <Servo.h>
#include <stdlib.h>

int servoPin = 7;
long servoPosition = 0;
Servo servo;
int angle;
int power;
int servoD = 5; //���������� ������ �� �����, ���� ������ ���� � ������������ �������
int servoV = 6; //���������� �� �����, ���� ������ ���� � ������������ �������
int motorD = 10; //���������� ������ �� ������, ���� ������ ���� � ������������ �������
int motorV = 11; //���������� �� ������, ���� ������ ���� � ������������ �������


int powerMax = 255;
int powerForward = 180; // 3.5 v from 5 v
int oldY = 0;

SoftwareSerial softSerial = SoftwareSerial(2, 3);

String portData = "";     // ���������� ������ �������
boolean endOfString = false;

void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);

  pinMode(servoD, OUTPUT);
  pinMode(servoV, OUTPUT);
  pinMode(servoD, OUTPUT);
  pinMode(motorV, OUTPUT);
  digitalWrite(servoD, HIGH);
  analogWrite(servoV, 0);   //5V from 7V, ���� servoD=HIGH, �� 0-������������, � 255 - ����, �� ����� ����� �����!!!!
  digitalWrite(motorD, HIGH);
  analogWrite(motorV, 255); // 125 - ��� 3.5 �� 7.3 ��� LOW, 130 ��� HIGH

  servo.attach(servoPin);
  servo.write(90);
}

void loop() {
  while (softSerial.available() > 0 && !endOfString) {
    char c = softSerial.read();    // ��������� ������ � ������
    if (c != '\n') portData += c;     // ���� ��� �� ������ ����� ������, �� ��������� ��� � ������
    else endOfString = true;
  }

  if (endOfString) {    // ���� ������� ������ ����� ������ �� ������ ������ �� ���� - �������� � ��������� � ��������
    Serial.println("portData: " + portData);
    String key = "", value = "";   // ����, ��������
    int i = 0;
    while (portData.length()>i) {
      if (portData[i]==' ') break;
      key += portData[i];
      i++;
    }
    if (portData[i] == ' ') {
      i++;
    }
    while (portData.length() > i) {
      value += portData[i];
      i++;
    }
//    Serial.println("key:" + key + "kakoy-to simvol");
//    Serial.println("value:" + value);
    portData = "";
    endOfString = false;

    if (key.equals("dir")) {  // ������ ��� ��������� �������� � ��������� � ��������������� = 1
      boolean boolJoy = false; //
      int i = 0;
      String valueX = "", valueY = "";
      while (value.length() > i){
        if (value[i] == ' ') boolJoy = true;
        if (value[i] != ' ' && !boolJoy) valueX += value[i];
        else if (value[i] != ' ' && boolJoy) valueY += value[i];
        i++;
      }
      int iValueX = valueX.toInt(); // ���������� X
      int iValueY = valueY.toInt(); // ���������� Y
//      Serial.println("valueX:" + valueX);
//      Serial.println("iValueX:" + String(iValueX));
      angle = map(-iValueX, -10, 10, 60, 120);
      Serial.println("Angle: " + String(angle));
      Serial.println("");
      servo.write(angle);
      SetPowerFromY(iValueY);
    }
    if(key.equals("L1on")){ //������ ��� ��������� ������������� � ��������������� = 2

    }
    if(key.equals("L1off")){    //������ ��� ���������� ������������� � ��������������� = 2

    }
  }
  delay(50);
}

void SetPowerFromY(int valY) {
  int power = 0;
  int startPower = 0; // ��������� ����
  if (valY >= -1 && valY <= 1) {
    valY = 0;
  }
  // ������
  if (valY >= 0) {
    digitalWrite(motorD, HIGH);
    startPower = powerMax - powerForward;
    power = map(abs(valY), 0, 10, powerMax, powerMax - powerForward);
  }
  // �����
  else {
    digitalWrite(motorD, LOW);
    startPower = powerForward;
    power = map(abs(valY), 0, 10, 0, powerForward);
  }

   if ((oldY * valY) <= 0 && valY != 0) {
    Serial.println("Start motor");
    analogWrite(motorV, startPower);
    delay(200);
  }
  analogWrite(motorV, power);
  oldY = valY;
}