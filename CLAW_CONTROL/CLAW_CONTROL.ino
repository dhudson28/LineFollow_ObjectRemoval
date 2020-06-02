//must have NewPing library installed, makes it easy to use the HC-SR04 Module
#include <NewPing.h>

//setup L298N
#define ENA 12
#define ENB 11

#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 10

//define switches
#define SW1 4
#define SW2 5

//Define pins used for NEWPING library for HC-04 Sonar
#define TRIGGER_PIN 2
#define ECHO_PIN 3

//Setup State Machine
const int STATE0 = 0;
const int STATE1 = 1;
const int STATE2 = 2;
const int FAULT = 999;
int state = STATE0;

int steps = 0;

//define the sonar

NewPing sonar(TRIGGER_PIN, ECHO_PIN, 13);

void setup() {
  
  //setup serial
  Serial.begin(9600);
  
  //Make the Pins active to drive the L298N
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //Set the pins the switch is connected to
  pinMode(SW1, OUTPUT);
  pinMode(SW2, OUTPUT);

  //Set speed for the Enable Pins
  digitalWrite(ENA, 150);
  digitalWrite(ENB, 150);

}

void loop() {
  delay(50);
  
  switch(state)
  {
    case STATE0:

      if(sonar.ping_cm() > 0 && sonar.ping_cm() < 5)
      {
        state=STATE1;
        Serial.println('b');
      }
      break;

    case STATE1:
      claw_close();
      steps++;
      delay(10);
      claw_break();
      if(digitalRead(SW1) == 1 && digitalRead(SW2) == 1)
      {
        state=STATE2;
      }
      else{
      //  state=FAULT;
      }
      delay(100);
      break;

    case STATE2:
      claw_break();
      Serial.println('r');
      delay(1000);
      Serial.println('b');
      delay(1000);
      claw_open();
      delay(300);
      claw_break();
      
      //run routine to open the claw same amount 
      //of time as it was closed for.
      if(steps > 1)
      {
        //Serial.println(steps);
        steps = steps - 1;
        delay(100);
        claw_break();
        delay(100);
        claw_open();
        delay(10);
      
      }
      
      delay(1000);
      Serial.println('c');
      state=STATE0;
      delay(100);
      break;
      
    //used for debugging
    /*
    case FAULT:
      Serial.print("fault");
      break;
      */
  }
}

//below I defined the functions of the claw
void claw_open(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void claw_close(){
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
 
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void claw_break(){
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
