#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuración de la pantalla I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C 0x27, 16 columnas y 2 filas

int i = 0; // ubicación de la memoria
int valor_cad; // variable para la conversión
int val_max; // valor máximo de rango
int val_min; // valor mínimo de rango

void setup() {
  Serial.begin(9600);  // Comunicación serial
  lcd.init(); // Inicializar la pantalla
  lcd.backlight(); // Encender la luz de fondo

  valor_cad = EEPROM.read(0);
  val_max = valor_cad + 5; // rango de error
  val_min = valor_cad - 5; // rango de error.
}

void loop() {
  int lectura_analogica = analogRead(A0) / 4; // lee y convierte valor analógico
  
  if (lectura_analogica > val_max || lectura_analogica < val_min) { // condición de salida de rango
    valor_cad = lectura_analogica; // actualizar valor en variable
    EEPROM.write(0, valor_cad); // escribe dato en la memoria
    val_max = valor_cad + 5; // rango max de error
    val_min = valor_cad - 5; // rango min de error
  }
    Serial.println(String("memoria: ") + String(valor_cad));
    lcd.setCursor(0,0); // ubicación en LCD
    lcd.print(String("memoria: ")+String(valor_cad)); // imprime datos

    Serial.println(String("cad: ") + String(analogRead(0)/4));
    lcd.setCursor(0,1); //ubicación en LCD
    lcd.print(String("cad: ")+String(analogRead(0)/4)); // imprime datos
    delay(300); // espera
    lcd.clear(); // borra LCD
}
