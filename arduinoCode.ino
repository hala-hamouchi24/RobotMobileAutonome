#include <Servo.h>          // Bibliothèque pour le servomoteur.
#include <NewPing.h>        // Bibliothèque de fonctions pour le capteur ultrason.

//les pins de L298N 

int enA = 4;
int in1 = 9;
int in2 = 8;

int enB = 5;
int in3 = 10;
int in4 = 11;

//les pins de ultrasonic sensor 
#define trig_pin A1//analog 
#define echo_pin A0 //analog 

#define maximum_distance 250
boolean goesForward = false;
int distance = 150;

NewPing sonar(trig_pin, echo_pin, maximum_distance); 
Servo servo_motor; //nom du servo


void setup(){
// Configuration des broches et initialisation
  //Serial.begin(9600);
  analogWrite(enA, 130);
	analogWrite(enB, 130);
 	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Éteindre les moteurs - État initial
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  
  servo_motor.attach(7); //pin du servo

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    // Si la distance mesurée est inférieure à 20 cm
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      turnRight();
      delay(500);
      moveStop();
    }
    else{
      turnLeft();
      delay(500);
      moveStop();
    }
  }
  else{ // Si la distance mesurée est supérieure à 20 cm
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){ // Fonction pour tourner le servo vers la droite 
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){ // Fonction pour tourner le servo vers la gauche
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
  delay(100);
}

int readPing(){ // Fonction pour mesurer la distance avec le capteur ultrason
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  // Fonction pour arrêter le mouvement
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void moveForward(){
 // Fonction pour avancer
  if(!goesForward){

    Serial.println("==moveForward==");

    goesForward=true;
    
    	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
  }
}

void moveBackward(){
// Fonction pour reculer
  goesForward=false;

  Serial.println("==moveBackward==");

  	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
  
}

void turnRight(){
 // Fonction pour tourner à droite
  Serial.println("==turnRight==");

 digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  
  
}

void turnLeft(){
 // Fonction pour tourner à gauche
  Serial.println("==turnLeft==");

  	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
}
