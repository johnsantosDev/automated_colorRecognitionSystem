#include <Servo.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
//7 and 8 for servomotors
#define ledred 9
#define ledorange 10
#define ledgreen 11
#define ledblue 12

Servo topServo;
Servo bottomServo;
int frequency = 0;
int color = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(ledred, INPUT);
  pinMode(ledorange, INPUT);
  pinMode(ledgreen, INPUT);
  pinMode(ledblue, INPUT);
  
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(7);
  bottomServo.attach(8);
  Serial.begin(9600);
}
void loop() {
  topServo.write(115);
  delay(500);
  for (int i = 115; i > 65; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(500);

  color = readColor();//variable qui stockera la couleur
  delay(10);
  /*switch (color) {
    case 1:
      bottomServo.write(22);
      break;
    case 2:
      bottomServo.write(45);
      break;
    case 3:
      bottomServo.write(72);
      break;
    case 4:
      bottomServo.write(90);
      break;
    case 5:
      bottomServo.write(0);
      break;
    case 6:
      bottomServo.write(0);
      break;
    case 0:
      break;
  } */
  delay(300);

  for (int i = 65; i > 29; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(200);
  for (int i = 29; i < 115; i++) {
    topServo.write(i);
    delay(2);
  }
  color = 0;
}
// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  //169  G= 345  B= 299
  if (R<180 & R>80 & G<330 & G>230) {
    color = 1; // Red
    Serial.println("Red color detected...");
    digitalWrite(ledred, HIGH);
    for (int i =0; i<=45; i++) {
      bottomServo.write(i);
      delay(20);
    }
    delay(200);
    for (int i = 45; i > 0; i--) {
      bottomServo.write(i);
      delay(20);
    }
    digitalWrite(ledred, LOW);
    bottomServo.write(0);
  }
  //R= 180  G= 334  B= 306
  else if (G<250 & G>150 & B<150 & B>260) {
    color = 2; // Orange
    Serial.println("Orange color detected...");
    digitalWrite(ledorange, HIGH);
    for (int i =0; i<=90; i++) {
      bottomServo.write(i);
      delay(20);
    }
    delay(200);
    for (int i = 90; i > 0; i--) {
      bottomServo.write(i);
      delay(20);
    }
    digitalWrite(ledorange, LOW);
    bottomServo.write(0);
  }
  //R= 56  G= 55  B= 85
  else if (R<70 & R>35 & G<75 & G>35) {
    color = 3; // Green
    Serial.println("Green color detected...");
    digitalWrite(ledgreen, HIGH);
    for (int i =0; i<=135; i++) {
      bottomServo.write(i);
      delay(20);
    }
    delay(200);
    for (int i = 135; i > 0; i--) {
      bottomServo.write(i);
      delay(20);
    }
    digitalWrite(ledgreen, LOW);
   bottomServo.write(0);
  }
  //R= 80  G= 72  B= 43 
  else if (G<98 & G>55 & B<60 & B>30) {
    color = 6; // Blue
    Serial.println("Blue color detected...");
    digitalWrite(ledblue, HIGH);
    for (int i =0; i<=180; i++) {
      bottomServo.write(i);
      delay(20);
    }
    delay(200);
    for (int i = 180; i > 0; i--) {
      bottomServo.write(i);
      delay(20);
    }
   digitalWrite(ledblue, LOW);
   bottomServo.write(0);
  }
  //R= 71  G= 98  B= 101
  else if (R<105 & R>35 & G<131 & G>70) {
    color = 4; // Yellow
    Serial.println("Yellow color detected..."); 
    //
  }
  else if (R<86 & R>26 & G<85 & G>35) {
    color = 5; // Brown
    Serial.println("Brown color detected...");
    //
  }
  else {
    Serial.println("no specific color detected...");
  }
  return color;
}
