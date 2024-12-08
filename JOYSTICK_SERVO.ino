#include <Servo.h>
Servo serv; //set the first servo, uses speed and direction to move.
Servo serv2; //set the second servo, uses angles to move

const int LRpin = A0;
const int UDpin = A2;
const int Bpin = 11;

int LR; // left = 0, right = 1024. input from the joystick
int UD; //up = 0, down = 1024. input from the joystick
int UD_nuet; // the Up and Down adjustments when it's in the middle.
int LR_nuet; // the Left and Right adjustments when it's in the middle.
//the joystick inputs an int of each side. from 0 = low, 522 = middle, 1024 = high

int B; //the amount of light that goes to the LED.
int d=90; //angel of the servo. 90=middle
int s; //speed of the servo
const int DZ = 15; //a buffer to the joystick

void setup() {
  serv.attach(6); 
  serv2.attach(9);
  Serial.begin(9600);
  //for once we read the nuetral values before we even move the Joystick
  LR_nuet = analogRead(LRpin); //read the original value of the joystick while it's in the middle
  UD_nuet = analogRead(UDpin); //read the original value of the joystick while it's in the middle
}

void loop() {
  LR = analogRead(LRpin);
  UD = analogRead(UDpin);

  Serial.print("LR: ");  
  Serial.print(LR);
  Serial.print("    ,UD: ");
  Serial.println(UD);


//UD ADJUSTMENTS:
  if (UD >= UD_nuet+DZ){ //if pressed down, fron 512 to 1024
    d = d+3; // angle of the servo
    s = 90; //speed of the servo. 90=stop
  }
  else if (UD <= UD_nuet-DZ){ //if pressed up. from 512 to 0
    d = d-3;    
    s= 90;  
  }
  else{
    s = 90;
    B = 160;
  }
  
  //LR ADJUSTMENTS:
  if (LR >= LR_nuet+DZ){ //if pressed right, fron 512 to 1024
    s = map(LR, 0, 1024, 0, 180);
    d = d;
    B = 0;

  }
  else if (LR <= LR_nuet-DZ){ //if pressed LEFT. from 512 to 0
    s = map(LR-DZ, 0, 1024, 0, 180);    
    d = d; 
    B = 0;
  }


  serv.write(s);
  serv2.write(d);
  analogWrite(Bpin, B);
}
