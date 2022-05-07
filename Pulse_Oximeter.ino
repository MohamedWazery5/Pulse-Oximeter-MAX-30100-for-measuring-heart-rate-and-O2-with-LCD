#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
 
#define REPORTING_PERIOD_MS     1000
 
PulseOximeter pox;
uint32_t tsLastReport = 0;
 
void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
  Serial.begin(9600);
 lcd.begin(16, 2);

    if (!pox.begin()) {
        lcd.println("FAILED");
        for(;;);
    } else {
        lcd.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop()
{    

    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
      
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Heart rate:");
        lcd.print(pox.getHeartRate());
        lcd.setCursor(0, 1);
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.print("%");
        tone(8,1000,250);
     
        tsLastReport = millis();
        
    }
  
}
