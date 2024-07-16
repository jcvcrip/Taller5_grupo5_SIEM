
/*
 * UNIDAD V: FUNCIONES ESPECÍFICAS
 * CÓDIGO 23 : MANEJO DE MODOS SLEEP
 * OBJETIVO: Realizar un control de modos sleep por medio de interrupciones por software y hardware
 * MODOS SLEEP Y DE AHORRO DE BATERÍA
 *  Consumo es de 100-500 mA.
 *  Ahorro de batería es hasta 10 mA.
 * Librerías:
 *        avr/sleep.h
 *        avr/power.h
 *         
 * Configuración:
 *     MODOS SLEEP
 *               set_sleep_mode(modo):
 *               modo-> SLEEP_MODE_IDLE
 *                      SLEEP_MODE_ADC                       
 *                      SLEEP_MODE_PWR_SAVE
 *                      SLEEP_MODE_STANDBY
 *                      SLEEP_MODE_PWR_DOWN
 *               sleep_enable(): Habilita el modo         
 *                                configurado
 *               sleep_mode(): Entra al modo configurado
 *               sleep_disable(): Deshabilita modo
 *                          
 */
#include<avr/power.h>
#include<avr/sleep.h>
#include<avr/wdt.h>
#include <MsTimer2.h>
#include<EEPROM.h>
int dato;
int on=0;

void(* resetFunc) (void) = 0; // esta es la funcion
//void on(void);

void setup() {
   dato=EEPROM.read(0);
   Serial.begin(9600);
   Serial.println("SETUP");
   if(dato==0){
    set_sleep_mode(SLEEP_MODE_STANDBY);
    sleep_enable();
    EEPROM.write(0,1);
    wdt_enable(WDTO_8S);
    }
    else{
    sleep_disable();
     EEPROM.write(0,0);
      MsTimer2::set(10000,tiempo); // configura timer 2 a un segundo
       MsTimer2::start();
    }
   attachInterrupt(0,encender,LOW);
}.

void loop() {
if(dato==0){
  Serial.println("ME DORMI :|");
  delay(20);
 sleep_mode(); //entra a dormir
}
 else{
  Serial.println("DESPIERTO :)");
  delay(1000);
  }
}

void tiempo(){
  Serial.println("ME DORMI :|");
  delay(20);
  sleep_mode();
 }

 void encender (){
    resetFunc();  // la llamo con esto 
 }