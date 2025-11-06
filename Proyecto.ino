#include <Servo.h> 
#include <LiquidCrystal_I2C.h>

//La parte de abajo son los pines donde se encuentra conectado cada botón y led.
int led1 = 12;
int led2 = 2;
int ledagua = 13;
float estado1;
float estado2;
//
int sensor1 = A2;
int sensor2 = A3;
int bomba = 4;
LiquidCrystal_I2C lcd(0x27,20,4); //Dirección de la pantalla y la cantidad de columnas y filas que tiene
Servo Servomotor;


void setup() {
  Serial.begin(9600);
  Servomotor.attach(9);
//Las siguientes 3 líneas son para el encendido de los distintos leds presentes.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(ledagua, OUTPUT);
  pinMode(bomba, OUTPUT);
  Serial.begin(9600);
lcd.init();
  lcd.backlight();
}
void loop() {
  float entrada1 = analogRead(sensor1);
  float entrada2= analogRead(sensor2);
  float porcentaje1= ((1023-entrada1)/1023)*100;
  float porcentaje2= ((1023-entrada2)/1023)*100;
lcd.setCursor(1,0);
  lcd.print("Planta 1: ");
  lcd.print(porcentaje1,1);
  lcd.print("%");
  lcd.print(" ");
  lcd.setCursor(1,1);
  lcd.print("Planta 2: ");
  lcd.print(porcentaje2,1);
  lcd.print("%");
  lcd.print(" ");
  delay(200);
  Serial.print("Nivel de agua: ");
  Serial.println(sensornivel);
  Serial.print("Lectura humedad sensor 1: ");
  Serial.println(entrada1);           // lo muestra en el monitor
  Serial.print("Lectura humedad sensor 2: ");
  Serial.println(entrada2);           // lo muestra en el monitor
 
  delay(500); // medio segundo entre lecturas

  if (entrada1 >= 900) {
    Servomotor.write(0);   // se mueve a 90
    digitalWrite(led1, HIGH);
    delay(1000);
    digitalWrite(ledagua, HIGH);
    digitalWrite(bomba,HIGH);
    delay (1000);
    digitalWrite(bomba,LOW);
    digitalWrite(ledagua, LOW);
    delay(1000);


  }
   else if (entrada2 >= 500) {
    Servomotor.write(180);   // se mueve a 180
    digitalWrite(led2, HIGH);
    delay(1000);
    digitalWrite(ledagua, HIGH);
    digitalWrite(bomba,HIGH);
    delay (1000);
    digitalWrite(bomba,LOW);
    digitalWrite(ledagua, LOW);
    delay(1000);
  }
   else {
    Servomotor.write(90);    // vuelve a 0 cuando no se pulsa
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);

       delay(1000);
  }


}
