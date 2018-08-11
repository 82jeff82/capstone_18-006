//Jeff
//Changes
//Rev A: Implemented Loop for shift register and inputs
//Rev B: Need to make inputs for buttons consistent 
#include <math.h>
//Pin connected to ST_CP of 74HC595
int latchPin = 3;
//Pin connected to SH_CP of 74HC595
int clockPin = 2;
////Pin connected to DS of 74HC595
int dataPin = 5;
int power = 0;

//Global Variables
//Pin connected to input A
int inputA = 11;
//Pin connected to input B
int inputB = 10;
//Pin connected to input C
int inputC = 9;
//Pin connected to input D
int inputD = 6;

int cycle = 0;

//temp variable
int temp=0;

//Array for inputs
bool outputArray[3][4];

//Pin Setup
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(inputA, INPUT);
  pinMode(inputB, INPUT);
  pinMode(inputC, INPUT);
  pinMode(inputD, INPUT);
}
//End of pin setup

//Main function: Loops forever
void loop() {
  int i, j;
  int buttonNumber=0;
  // count from 0 to 255 and display the number
  // on the LEDs
  while (1) {
    if (power > 7)
    {
      buttonNumber=1;
      Serial.print("Printing Cycle ");
      Serial.print(cycle);
      Serial.print(":\n");
      
      /*Temporary Code to read the input of the thing
        
      
        for (j = 0; j < 3 ; j++) {
          Serial.print("Button ");
          Serial.print(buttonNumber);
          Serial.print(":");
          Serial.print(outputArray[j][3]);
          Serial.print("\n");
          buttonNumber++;
        }
        */
      //Old code for printing out the status of the buttons
      for (i = 0; i < 4 ; i++) {
        for (j = 0; j < 3 ; j++) {
          Serial.print("Button ");
          Serial.print(buttonNumber);
          Serial.print(":");
          Serial.print(outputArray[j][i]);
          Serial.print("\n");
          buttonNumber++;
        }
      }
      
      Serial.print("\n");
      power = 0;
    }

    
    // take the latchPin low so
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, LSBFIRST, powerOf(2, power));
    /*
    Serial.print("Power = ");
    Serial.print(powerOf(2, power));
    Serial.print("\n");
    */
    //delay(20);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:

    /*Temp code
    Serial.print("I have reached the power =");
    Serial.print(power);
    Serial.print("point \n");
    */
    if ((power == 1) || (power == 0) || (power == 2))
    {
      //Temproary code, need to fix

     
     //temp=power;
      
      outputArray[power][0] = digitalRead(inputA);
      outputArray[power][1] = digitalRead(inputB);
      outputArray[power][2] = digitalRead(inputC);
      outputArray[power][3] = digitalRead(inputD);
      /*For debugging Purposes:
      Serial.print("Button A = ");
      Serial.print(outputArray[power][0]);
      Serial.print("\n");
      Serial.print("Button B = ");
      Serial.print(outputArray[power][1]);
      Serial.print("\n");
      Serial.print("Button C = ");
      Serial.print(outputArray[power][2]);
      Serial.print("\n");
      Serial.print("Button D = ");
      Serial.print(outputArray[power][3]);
      Serial.print("\n");
      */
    }
    delay(100);
    cycle++;
    power++;
  }
}

int powerOf(int base, int power)
{
  int result = 1;
  int i;
  int invert=0b11111111;
  for (i = 0; i < power; i++)
  {
    result = result * base;

  }
  
  result=invert^result;
  return result;
}
