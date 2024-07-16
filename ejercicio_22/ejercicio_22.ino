#include<avr/wdt.h>
#include <EEPROM.h>
#include <MsTimer2.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C y tamaño de la pantalla

int j;

void setup(){
  lcd.init();
  lcd.backlight();
  attachInterrupt(digitalPinToInterrupt(2), on, FALLING);
  // attachInterrupt(2,on,LOW);
  MsTimer2::set(9000, conteo);
  j=EEPROM.read(0);
  if(j == 1){
    MsTimer2::start();
    Serial.begin(19200);

  
  } else {
    Serial.begin(9600);
    wdt_disable();
    MsTimer2::stop();

  }

  lcd.print("INICIO");
  lcd.setCursor(0, 1);
  Serial.println("INICIO");
}

void loop(){
  Serial.println(j);
  lcd.setCursor(0, 1);
  lcd.print("J : ");
  lcd.print(j);
  lcd.print("                   ");
  delay(200);
}

void on(){
  MsTimer2::start();
  j = 1 - j;
  EEPROM.update(0,j);
  if(j == 0)
    MsTimer2::stop();
}

void conteo(){
  Serial.println("timer");
  lcd.setCursor(0, 1);
  lcd.print("timer");
  if(j == 1){
    wdt_enable(WDTO_1S);
  }
}

