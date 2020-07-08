/*------ Fire Fighting Robot ----- */

#include <Servo.h>
Servo myservo;

int pos = 0;
boolean fire = false;

/*------- Inputs------*/
#define Left_S 9      // left sensor
#define Right_S 10      // right sensor
#define Forward_S 8 //forward sensor

/*------- Outputs------*/
#define LM1 2       // left motor
#define LM2 3       // left motor
#define RM1 4       // right motor
#define RM2 5       // right motor
#define pump 6

void setup()
{
  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);

  Serial.begin(9600);
  myservo.attach(11);
  myservo.write(90);
}

void put_off_fire()
{
  delay (500);

  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);

  digitalWrite(pump, LOW); delay(500);

  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }

  digitalWrite(pump, HIGH);
  myservo.write(90);

  fire = false;
}

void loop()
{
  Serial.println("acddddsdsd");//demo test
  digitalWrite(pump, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  myservo.write(90); //Sweep_Servo();

  if (digitalRead(Left_S) == 1 && digitalRead(Right_S) == 1 && digitalRead(Forward_S) == 1) //agun nai , sensor er value 0
  {
    //Do not move the robot
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  }

  else if (digitalRead(Forward_S) == 0) //agun shamne
  {
    //Move the robot forward
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);


    fire = true;
  }

  else if (digitalRead(Left_S) == 0) //agun bam dike
  {
    //Move the robot left
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
  }

  else if (digitalRead(Right_S) == 0) //agun dan dike
  {
    //Move the robot right
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);

  }

  delay(300); //Slow down the speed of robot

  while (fire == true)
  {
    put_off_fire();
    Serial.println("agun agun agun !!!!!");
   
  }
}
