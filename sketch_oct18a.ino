#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define analogPin      0         
#define chargePin      13        
#define dischargePin   3       
#define resistorValue  10000.0F  //Remember, we've used a 10K resistor to charge the capacitor

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;               
float nanoFarads;

void setup(){
  pinMode(chargePin, OUTPUT);    
  digitalWrite(chargePin, LOW);
  lcd.begin(16, 2);  //LCD order

}

void loop(){
  digitalWrite(chargePin, HIGH); 
  startTime = micros();
  while(analogRead(analogPin) < 648){      
  }

  elapsedTime= micros() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) ;

    
 
  if (microFarads > 1){

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Capacitor = ");
    lcd.setCursor(0,1); 
    lcd.print(microFarads);
    lcd.setCursor(9,1);       
    lcd.print("uF");  
    delay(500);   
  }

  else{
    nanoFarads = microFarads * 1000.0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Capacitor = ");
    lcd.setCursor(0,1);      
    lcd.print(nanoFarads-11.2); 
    lcd.setCursor(9,1);      
    lcd.print("nF");         
    delay(500);
  }

 
 
  digitalWrite(chargePin, LOW);           
  pinMode(dischargePin, OUTPUT);           
  digitalWrite(dischargePin, LOW);     //discharging the capacitor    
  while(analogRead(analogPin) > 0){        
  }//This while waits till the capaccitor is discharged

  pinMode(dischargePin, INPUT);      //this sets the pin to high impedance


}