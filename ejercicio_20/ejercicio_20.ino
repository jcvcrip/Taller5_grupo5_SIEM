#include <EEPROM.h> // librería EEPROM
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuración de la pantalla I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // Direccion I2C 0x27, 16 columnas y 2 filas

int var = 0; // variable de conteo

void setup() {
  Serial.begin(9600);  // Comunicación serial
  lcd.init(); // Inicializar la pantalla
  lcd.backlight(); // Encender la luz de fondo

  EEPROM.get(0, var); // lee el dato en la EEPROM en la variable var
  Serial.println(String("valor: ") + String(var));   // imprime valor en el serial
  lcd.setCursor(0, 0);
  lcd.print("Valor: ");
  lcd.setCursor(0, 1);
  lcd.print(var); // imprime valor en la pantalla LCD
}

void loop() {
  var++; // incremento de variable
  if (var < 255) // condición 
    EEPROM.put(0, var); // actualiza valor
  else
    var = 0; // reinicia variable

  Serial.println(String("valor: ") + String(var)); // imprime por serial
  lcd.clear(); // limpia la pantalla
  lcd.setCursor(0, 0);
  lcd.print("Valor: ");
  lcd.setCursor(0, 1);
  lcd.print(var); // imprime valor en la pantalla LCD

  delay(2000);   
}
