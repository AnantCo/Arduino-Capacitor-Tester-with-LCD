# Arduino-Capacitor-Tester-with-LCD
Arduino project to measure capacitor values using a 10K resistor and display results on an LCD.


# Arduino Capacitor Tester with LCD

This Arduino project measures the capacitance of a capacitor using a 10KΩ resistor and displays the result on a 16x2 LCD display. It calculates both microfarad (μF) and nanofarad (nF) values based on the capacitor’s charging time.

---

## 🧰 Components Used
- Arduino Uno
- 10KΩ Resistor
- 16x2 LCD Display
- Breadboard & Jumper Wires
- Capacitors for testing

---

## ⚙️ Circuit Connections
| Component | Arduino Pin |
|------------|--------------|
| LCD RS     | 7            |
| LCD E      | 8            |
| LCD D4     | 9            |
| LCD D5     | 10           |
| LCD D6     | 11           |
| LCD D7     | 12           |
| Charge Pin | 13           |
| Discharge Pin | 3         |
| Analog Input | A0         |

---

## 🧠 Working Principle
1. The capacitor is charged through a 10KΩ resistor.
2. The Arduino measures the time it takes for the voltage to reach 63.2% of the supply voltage (around 648 out of 1023 in analog value).
3. Using the RC charging equation, capacitance is calculated:
   \[
   C = \frac{t}{R}
   \]
4. The value is displayed on the LCD in μF or nF.

---

## 📜 Arduino Code
```cpp
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define analogPin      0         
#define chargePin      13        
#define dischargePin   3       
#define resistorValue  10000.0F  // 10K resistor

unsigned long startTime;
unsigned long elapsedTime;
float microFarads;               
float nanoFarads;

void setup() {
  pinMode(chargePin, OUTPUT);    
  digitalWrite(chargePin, LOW);
  lcd.begin(16, 2);
}

void loop() {
  digitalWrite(chargePin, HIGH); 
  startTime = micros();
  while (analogRead(analogPin) < 648) {}
  elapsedTime = micros() - startTime;
  microFarads = ((float)elapsedTime / resistorValue);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Capacitor = ");
  lcd.setCursor(0, 1);

  if (microFarads > 1) {
    lcd.print(microFarads);
    lcd.print(" uF");
  } else {
    nanoFarads = microFarads * 1000.0;
    lcd.print(nanoFarads - 11.2);
    lcd.print(" nF");
  }

  delay(500);
  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);
  while (analogRead(analogPin) > 0) {}
  pinMode(dischargePin, INPUT);
}
