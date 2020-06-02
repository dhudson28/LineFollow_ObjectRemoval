
//define pins
#define Left_IR 2
#define Right_IR 10
#define Center_IR 4

//Set to opposite of value
#define Left_Read_IR !digitalRead(Left_IR)
#define Center_Read_IR !digitalRead(Center_IR) 
#define Right_Read_IR !digitalRead(Right_IR)

//setup pins for the L298N
#define ENA 5
#define ENB 6

#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

//setup variables
int carSpeed = 100;

int right_distance = 0;
int middle_distance = 0;
int left_distance = 0;

unsigned long Count_Millis;
unsigned char claw_message;

void setup() {
  
  //Setup the IR Sensors for Line Following
  pinMode(Left_IR, INPUT);
  pinMode(Center_IR, INPUT);
  pinMode(Right_IR, INPUT);

  //Setup MotorControls 
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //Begin Serial
  Serial.begin(9600);

}

//Here I define the motor functions
void forward(int carSpeed)
  {
    analogWrite(ENA, carSpeed);
    analogWrite(ENB, carSpeed);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

void back(int carSpeed)
  {
    analogWrite(ENA, carSpeed);
    analogWrite(ENB, carSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

void right(int carSpeed)
  {
    analogWrite(ENA, carSpeed);
    analogWrite(ENB, carSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }

void left(int carSpeed)
  {
    analogWrite(ENA, carSpeed);
    analogWrite(ENB, carSpeed);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

void brake()
  {
    digitalWrite(ENA, LOW);
    digitalWrite(ENB, LOW);
  }

//Begin the program
void loop() {

  char claw_message = Serial.read();
  if(Serial.available() > 0){
  char claw_message = Serial.read();
  delay(500);
  switch(claw_message)
    {
      case 'r':
        right(150);
        delay(100);
        brake();
      
        break;
      case 'b':
        brake();
        delay(500);
        break;
    
      case 'l':
        left(150);
        delay(100);
        brake();
        break;
    
      case 'c':
        break;
    
      default:
        if(Center_Read_IR)
        {
          forward(180);
          Count_Millis = millis();
        }

        else if(Right_Read_IR)
        {
          right(180);
          Count_Millis = millis();
        }

        else if(Left_Read_IR)
        {
          left(180);
          Count_Millis = millis();
        }
       else
       {
          if (millis() - Count_Millis > 150)
          {
            brake();
          }
        }
      }
  }
}
