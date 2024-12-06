#include <SoftwareSerial.h> //biblo qui permet de communiquer avec le bluetooth via une communication serie

int bluetoothTx = 3;
int bluetoothRx = 2;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);//creation d une instance de la classe softwareserial

char cmd;// variable pour stocker la commande Bluetooth reçue

//les pins de L298N 
const int rightMotorForward = 8;
const int rightMotorBackward = 9;
int enA = 4;// controle de la vitesse du rightmotor

const int leftMotorForward = 11;
const int leftMotorBackward = 10;
int enB = 5;// controle de la vitesse du leftmotor
 
void setup() {
   bluetooth.begin(115200);// Initialisation de la communication série avec le module Bluetooth à 115200 bauds
  bluetooth.print("$$$"); // Envoi de la séquence de commandes spéciales au module Bluetooth
  delay(100);
  bluetooth.println("U,9600,N");// Configuration du module Bluetooth avec une vitesse de 9600 bauds
  bluetooth.begin(9600); // Réinitialisation de la communication série avec le module Bluetooth à 9600 bauds
  analogWrite(enA, 170);// Configuration de la vitesse du moteur droit
	analogWrite(enB, 170);// Configuration de la vitesse du moteur gauche
  pinMode(leftMotorForward,OUTPUT);   
  pinMode(leftMotorBackward,OUTPUT);   
  pinMode(rightMotorForward,OUTPUT);   
  pinMode(rightMotorBackward,OUTPUT);   
}
 
void loop() {
  if(bluetooth.available()){
    cmd = bluetooth.read(); // Lecture de la commande Bluetooth
  }
   
  if(cmd == 'F'){  
    // Mouvement en avant
    Serial.print(cmd);         
    digitalWrite(leftMotorForward,HIGH);
    digitalWrite(rightMotorForward,HIGH);
  }
   
  else if(cmd == 'B'){   
    // Mouvement en arrière   
    digitalWrite(leftMotorBackward,HIGH);
    digitalWrite(rightMotorBackward,HIGH);
  }
   
  else if(cmd == 'L'){ 
    // Virage à gauche     
    digitalWrite(rightMotorForward,HIGH);
  }
   
  else if(cmd == 'R'){   
    // Virage à droite   
    digitalWrite(leftMotorForward,HIGH);
  }
   
  else{ // Arrêt (tous les moteurs s'arrêtent)     
    digitalWrite(leftMotorForward,LOW);
    digitalWrite(leftMotorBackward,LOW);
    digitalWrite(rightMotorForward,LOW);
    digitalWrite(rightMotorBackward,LOW);
  }
}