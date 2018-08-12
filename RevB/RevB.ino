//Rev A: Implemented Loop for shift register and inputs
//Rev B: Need to make inputs for buttons consistent 
#include <math.h>
//Pin connected to ST_CP (RCLK) pin 12 of 74HC595
int rclkPin = 10; //
//Pin connected to SH_CP (SRCLK) pin 11 of 74HC595
int srclkPin = 6;  //Working
////Pin connected to DS (SER) pin 14 of 74HC595
int serPin = 11;  //Working

//Global Variables
//Pin connected to input A
int inputA = 0;
//Pin connected to input B
int inputB = 1;
//Pin connected to input C
int inputC = 2;
//Pin connected to input D
int inputD = 3;

//Value to be shifted out
uint8_t data = 1;

uint8_t data_shifted = 8;

int cycle = 0;

//temp variable
int temp=0;

//Array for inputs
bool outputArray[3][4];

//Pin Setup
void setup() {
  pinMode(rclkPin, OUTPUT);
  pinMode(srclkPin, OUTPUT);
  pinMode(serPin, OUTPUT);
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
    if (data_shifted >= 8)
    {
      buttonNumber=1;
      Serial.print(":\n");
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
      Serial.print("Printing Cycle ");
      Serial.print(cycle);
    }

    if (data_shifted>=8) 
    {
      digitalWrite(srclkPin, HIGH);
      digitalWrite(rclkPin, LOW);
      digitalWrite(serPin, HIGH);
      data_shifted = 1;
      delay(20);
    }
    else
    {
      digitalWrite(srclkPin, HIGH);
      digitalWrite(rclkPin, LOW);
      digitalWrite(serPin, LOW);
      data_shifted++;
      delay(20);
    }
    
    if ((data_shifted-1) <= 2) 
    {
      outputArray[data_shifted-1][0] = digitalRead(inputA);
      outputArray[data_shifted-1][1] = digitalRead(inputB);
      outputArray[data_shifted-1][2] = digitalRead(inputC);
      outputArray[data_shifted-1][3] = digitalRead(inputD);
    }
    digitalWrite(srclkPin, LOW);
    digitalWrite(rclkPin, HIGH);
    delay(20);
  }
}


