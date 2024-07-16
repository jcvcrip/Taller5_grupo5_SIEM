#include<avr/wdt.h>
#include<EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C y tamaño de la pantalla

int i;

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("DESPIERTO");
  Serial.println("DESPIERTO");
  attachInterrupt(0,activacion,LOW);
  i=EEPROM.read(0);
}

void loop(){
  Serial.println(i++);
  lcd.setCursor(0, 1);
  lcd.print(i);
  lcd.print("                ");
  if(i<255){
    EEPROM.write(0,i);
  } else {
    i=0;
  }
  delay(300);
}

void activacion(){
  wdt_disable();
  wdt_enable(WDTO_4S);
}
