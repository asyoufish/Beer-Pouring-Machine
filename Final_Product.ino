#include <Stepper.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

// initialize the stepper library on pins 4 through 7, 8 through 11:
AccelStepper stepper1(AccelStepper::FULL4WIRE , 4, 5, 6, 7);//sensorpin2 bottle
AccelStepper stepper2(AccelStepper::FULL4WIRE , 8, 9, 10, 11);//sensorpin3 cup

int cupup = 1;
int bottleup =1;
int BottleVal;
int BeerVal;
void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(A3,OUTPUT);// for ENA
  analogWrite(A3,1023);// enable ENA
  pinMode(A2,OUTPUT);// for ENB
  analogWrite(A2,1023); // enable ENB
  pinMode(A4,OUTPUT);// for ENA
  analogWrite(A4,1023);// enable ENA
  pinMode(A5,OUTPUT);//for ENB
  analogWrite(A5,1023);// enable ENB

  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
    
  stepper2.setMaxSpeed(1000.0);
  stepper2.setAcceleration(100.0);
}

void loop(){
    //sense both bottle and cup 
    if (digitalRead(2)==0 & digitalRead(3)==0 & bottleup==1){
    //The maximum height bottle=2200, cup=1000
      stepper1.moveTo(1000); //bottle up
      stepper2.moveTo(1000); //cup up
      stepper1.run();
      stepper2.run();
      cupup = 0;
    }
    //sense nothing
    else if (digitalRead(2)==1 & digitalRead(3)==1 & cupup==0){

      stepper1.moveTo(2200);//bottle up
      stepper2.moveTo(0);//cup down

      stepper1.run();
      stepper2.run();
     // delay(0);
      bottleup = 0;
    }
    //sense the cup but no bottle
    else if (digitalRead(2)==1 & digitalRead(3)==0 & bottleup==0 & cupup==0){

      stepper1.moveTo(0);//botle down
      stepper2.moveTo(0);//cup down
      
      stepper1.run();
      stepper2.run();
      //delay(0);
    } 
    else if (digitalRead(2)==0 & digitalRead(3)==0 & bottleup==0 & cupup==0){

      stepper1.moveTo(0);//botle down

      stepper1.run();
     // delay(0);
      cupup = 1;
    }
}
