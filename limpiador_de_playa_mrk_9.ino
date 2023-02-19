#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

//servomotores
Servo servo1;
Servo servo2;
//puetos de control de velocidad
int enA = 10;
int enB = 11;
//ULTRASONICO 1
const int Trigger = 2;
const int Echo = 3;
//ULTRASONICO 2
const int Trigger_2 = 5;
const int Echo_2 = 4;
//ULTRASONICO 3
const int Trigger_3 = 7;
const int Echo_3 = 6;
//ULTRASONICO 4
const int Trigger_4 = 36;
const int Echo_4 = 37;
//motor A
const int pinIN1 = 8;
const int pinIN2 = 9;
//motor b
const int pinIN3 = 12;
const int pinIN4 = 13;
//variables para distancia y tiempo
long d_1, d_2, d_3, d_4, t_1, t_2, t_3, t_4;

void setup() {
  
  lcd.init();//inciamos lcd
  lcd.backlight();// se activa la luz de fondo
  lcd.clear();
  //pines de servomotores
  servo1.attach(20);
  servo2.attach(21);
  Serial.begin(9600);//abrimos un monitor serial
  //declaracion de ultrasonicos
  //ULTRASONICO 1
  pinMode(Trigger, OUTPUT); //indicamos que el puerto sera salida
  pinMode(Echo, INPUT); //indicamos que el puerto sera entrada
  digitalWrite(Trigger, LOW); //escribimos un 0 en trig
  //ULTRASONICO 2
  pinMode(Trigger_2, OUTPUT); //indicamos que el puerto sera salida
  pinMode(Echo_2, INPUT); //indicamos que el puerto sera entrada
  digitalWrite(Trigger_2, LOW); //escribimos un 0 en trig
  //ULTRASONICO 3
  pinMode(Trigger_3, OUTPUT); //indicamos que el puerto sera salida
  pinMode(Echo_3, INPUT); //indicamos que el puerto sera entrada
  digitalWrite(Trigger_3, LOW); //escribimos un 0 en trig
  //ULTRASONICO 4
  pinMode(Trigger_4, OUTPUT); //indicamos que el puerto sera salida
  pinMode(Echo_4, INPUT); //indicamos que el puerto sera entrada
  digitalWrite(Trigger_4, LOW); //escribimos un 0 en trig
  //puertos en salida para control de velocidad
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(pinIN1, OUTPUT); 
  //indicamos que los motores seran salida
  pinMode(pinIN2, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  //servos inician en 0°
  servo1.write(0);
  servo2.write(0);
  
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("S1 ");
  lcd.print(d_1);
  lcd.setCursor(0, 1);
  lcd.print("S2 ");
  lcd.print(d_2);
  lcd.setCursor(0, 2);
  lcd.print("S3 ");
  lcd.print(d_3);
  lcd.display();
  delay(300);
  lcd.clear();
  
//ULTRASONICO 1
digitalWrite(Trigger, HIGH); //escribimos un 1 en trig
delayMicroseconds(10); //genera un pulso por 10microsegundos
digitalWrite(Trigger, LOW);

t_1 = pulseIn(Echo, HIGH); //leemos el sensor
d_1 = t_1 / 58.2; //formula para calcular la distancia en cm
Serial.print("Distancia 1: ");
Serial.println(d_1); //imprimimos la distancia

//ULTRASONICO 2
digitalWrite(Trigger_2, HIGH); //escribimos un 1 en trig
delayMicroseconds(10); //genera un pulso por 10microsegundos
digitalWrite(Trigger_2, LOW);

t_2 = pulseIn(Echo_2, HIGH); //leemos el sensor
d_2 = t_2 / 58.2; //formula para calcular la distancia en cm
Serial.print("Distancia 2: ");
Serial.println(d_2);

//ULTRASONICO 3
digitalWrite(Trigger_3, HIGH); //escribimos un 1 en trig
delayMicroseconds(10); //genera un pulso por 10microsegundos
digitalWrite(Trigger_3, LOW);

t_3 = pulseIn(Echo_3, HIGH); //leemos el sensor
d_3 = t_3 / 58.2; //formula para calcular la distancia en cm
Serial.print("Distancia 3: ");
Serial.println(d_3);

  if (d_1 <= 70 ){//para

  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, LOW); 
  
  servo1.write(0);
  servo2.write(180);
  delay(3000);
  servo1.write(180);
  servo2.write(0);
  }else if (d_1 <= 70 && d_2 <= 50){//derecha
  analogWrite(enA, 105);
  analogWrite(enB, 105);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
  delay(500);
  }else if (d_1 <= 70 && d_3 <=50){//izquierda
  analogWrite(enA, 105);
  analogWrite(enB, 105);
  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
  delay(500);
  }else if(d_1 <= 70 && d_2 <= 50 && d_3 <= 50){//reversa
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
  delay(500);
  
  }else if(d_1 > 70){//recta
  analogWrite(enA, 70);
  analogWrite(enB, 70);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
  }
}
