#include <Servo.h>

int M1_Left = 12; //Direccion M1
int M1_Right = 11; //Direccion M1

int M2_Left = 9; //Direccion M2
int M2_Right = 10; //Direccion M2

Servo miServo;
int angle = 90;
long distance;
long time;

void setup()
{
  Serial.begin(9600);
  pinMode(M1_Left, OUTPUT);
  pinMode(M1_Right, OUTPUT);
  pinMode(M2_Left,OUTPUT);
  pinMode(M2_Right, OUTPUT);
  
  miServo.attach(7);
  
  pinMode(6, OUTPUT); /*ultrasonic sensor pulse output*/
  pinMode(5, INPUT); /*time sensor pulse back*/
}

void loop(){
   // girar (1,1); 
   // delay(1000); //1 sg 
 
   // girar (2,1); 
   // delay(1000); //1 sg 
  
   // girar (1,2); 
   // delay(1000); //1 sg 
 
   // girar (2,2); 
   // delay(1000); //1 sg 
    
   moveForward();
   delay(1000); //1 sg 
  
    if(scanObstacle())
       avoidObstacle();
}

boolean scanObstacle()
{
  moveServo();
  
  digitalWrite(6,LOW); /* sensor stabilization*/
  delayMicroseconds(5);
  digitalWrite(6, HIGH); /* write ultrasonic pulse */
  delayMicroseconds(10);
  time=pulseIn(5, HIGH); /* Function to measure the length in an incoming pulse. It measures the time through an pulse output and the incoming pulse. In other words, it measures since the pin 12 starts to receives the rebound, HIGH, until it doesnt receive any rebound, LOW.

  distance= int(0.017*time); /* Calculates the distance

  /* Serial monitor - distance */
  Serial.println("Distance ");
  Serial.println(distance); 
  Serial.println(" cm");
  delay(1000); 
 
  if(distance<20 && distance!=0)
     return true;
  else
     return false;
}

void moveServo(){
  for(int n=0; n<100; n++){
   angle+=40;
   miServo.write(angle);
   Serial.print("Angulo:" + angle);
   delay(100);
 }
}

void avoidObstacle()
{
   turn (1,1); 
   delay(1000); //1 sg 
   
   turn (1,1); 
   delay(1000); //1 sg 
   
   turn (1,1); 
   delay(1000); //1 sg 
}


void moveForward()
{
  boolean inPin1 = HIGH;
  boolean inPin2 = HIGH;
  
  //digitalWrite(M1_Izq, inPin1);
  digitalWrite(M1_Derecha, inPin2);
  //digitalWrite(M2_Izq, inPin1);
 digitalWrite(M2_Derecha, inPin2);
}

void turn(int direccion, int motor)
{
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direccion == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }
  
  if(motor == 1){
    digitalWrite(M1_Izq, inPin1);
    digitalWrite(M1_Derecha, inPin2);
  }else{
    digitalWrite(M2_Izq, inPin1);
    digitalWrite(M2_Derecha, inPin2);
  }

}

void stop(int motor){
    if(motor == 1){
     digitalWrite(M1_Left, LOW);
     digitalWrite(M1_Right, LOW);
    }else{
     digitalWrite(M2_Left, LOW);
     digitalWrite(M2_Right, LOW);
    }
}

