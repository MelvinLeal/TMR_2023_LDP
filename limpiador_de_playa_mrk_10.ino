#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

//servomotores
//Servo servoizq;
//Servo servoder;
//boton de encendido
boolean encendido = true;
//int boton = 32;
int estadoboton;
//temporizador
int segundos;
int minutos;
//puetos de control de velocidad
int enA = 6;
int enB = 7;
//ULTRASONICO 1
const int Trigger = 22;
const int Echo = 23;
//ULTRASONICO 2
const int Trigger_2 = 24;
const int Echo_2 = 25;
//ULTRASONICO 3
const int Trigger_3 = 26;
const int Echo_3 = 27;
//ULTRASONICO 4
const int Trigger_4 = 28;
const int Echo_4 = 29;
//motor A
const int pinIN1 = 2;
const int pinIN2 = 3;
//motor b
const int pinIN3 = 4;
const int pinIN4 = 5;
//variables para distancia y tiempo
long d_1, d_2, d_3, d_4, t_1, t_2, t_3, t_4;
int inicio;
int velocidad = 250;
/*int pinacelerador = 33;
int acelerador;
int pindesacelerador = 34;
int desacelerador;
const int analogPin = A8;
int value;
int posicion, posicion2;*/

void setup() {
  //declaracion de boton
//  pinMode(boton, INPUT);
  lcd.init();//inciamos lcd
  lcd.backlight();// se activa la luz de fondo
  lcd.clear();
  //pines de servomotores
  //servoizq.attach(39);
  //servoder.attach(38);
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
  //indicamos que los motores seran salida
  pinMode(pinIN1, OUTPUT); 
  pinMode(pinIN2, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
//pinMode(pinacelerador, INPUT);
//pinMode(pindesacelerador, INPUT);

    // Configuracion del timer1 
  TCCR1A = 0;                        // El registro de control A queda todo en 0, pines OC1A y OC1B deshabilitados
  TCCR1B = 0;                        //limpia el registrador
  TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1
  TCNT1 = 0xC2F8;                    // inicia timer para desbordamiento 1 segundo
                                     // 65536-(16MHz/1024/1Hz - 1) = 49912 = 0xC2F8
  
  TIMSK1 |= (1 << TOIE1);           // habilita la interrupcion del TIMER1
}


void loop() {
if(encendido){
  lcd.setCursor(15, 3);
  lcd.print("v=");
  lcd.print(velocidad);
  lcd.setCursor(18, 0);
  lcd.print("ON");
  lcd.setCursor(0, 0);
  lcd.print("S1=");
  lcd.print(d_1);
  lcd.setCursor(0, 1);
  lcd.print("S2=");
  lcd.print(d_2);
  lcd.setCursor(0, 2);
  lcd.print("S3=");
  lcd.print(d_3);
  lcd.setCursor(0, 3);
  lcd.print("S4=");
  lcd.print(d_4);
  lcd.setCursor(12, 1);
  lcd.print("T1=");
  lcd.print(minutos);
  lcd.print(":");
  lcd.print(segundos);
  lcd.display();
  delay(100);
  lcd.clear();
}
if(!encendido){
    lcd.setCursor(0, 0);
    lcd.print("SYSTEM OFF");
    lcd.display();
    delay(100);
    lcd.clear();
}
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

//ULTRASONICO 4
digitalWrite(Trigger_4, HIGH); //escribimos un 1 en trig
delayMicroseconds(10); //genera un pulso por 10microsegundos
digitalWrite(Trigger_4, LOW);

t_4 = pulseIn(Echo_4, HIGH); //leemos el sensor
d_4 = t_4 / 58.2; //formula para calcular la distancia en cm
Serial.print("Distancia 3: ");
Serial.println(d_4);
//codigo de inico del boton
/*  value = analogRead(analogPin);
  posicion = map(value, 0, 1023, 0, 180);
  posicion2 = map(value, 0, 1023, 180, 0);
  delay(100);
  servoizq.write(posicion);
  servoder.write(posicion2);
  acelerador = digitalRead(pinacelerador);
  if(acelerador == 1)
  {
    velocidad=velocidad+50;
    delay(100);
    if(velocidad>=255)
    {
      velocidad=255;
    }
  }
  desacelerador = digitalRead(pindesacelerador);
  if(desacelerador == 1)
  {
    velocidad=velocidad-50;
    delay(100);
    if(velocidad<=5)
    {
      velocidad=0;
    }
    }
estadoboton = digitalRead(boton);
 if (estadoboton == 1 && !encendido)
 {
  encendido = true;
  delay(100);
 } else if(estadoboton == 1 && encendido)
 {
  encendido = false;
  delay(100);
 }
 estadoboton = encendido;*/
 ////////////////////////////
   if (!encendido){//detenido
    analogWrite(enA, velocidad);
    analogWrite(enB, velocidad);
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, LOW);
    digitalWrite(pinIN3, LOW);
    digitalWrite(pinIN4, LOW);
    lcd.setCursor(17, 2);
    lcd.print("|O|");
    lcd.display();
    delay(100);
   }
      if (d_4 <= 10 && encendido ){//detenido con sensor de llenado
    analogWrite(enA, velocidad);
    analogWrite(enB, velocidad);
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, LOW);
    digitalWrite(pinIN3, LOW);
    digitalWrite(pinIN4, LOW); 
    lcd.setCursor(16, 2);
    lcd.print("FULL");
    delay(100);
   }
    if (minutos == 5 && encendido){//detenido
    minutos = 5; segundos = 0;
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, LOW);
    digitalWrite(pinIN3, LOW);
    digitalWrite(pinIN4, LOW); 
    lcd.setCursor(17, 2);
    lcd.print("|O|");
    lcd.display();
    delay(50);
   }else if (d_1 <= 70 && d_2 <=70 && d_3 <= 70 && d_4 > 10 && encendido){//izquierda
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW); 
    lcd.setCursor(17, 2);
    lcd.print("=>");
    lcd.display();
    delay(100);
  }else if (d_1 <= 70 && d_2 > 70 && d_3 > 70 && d_4 > 10 && encendido){//derecha
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
    lcd.setCursor(17, 2);
    lcd.print("<=");
    lcd.display();
    delay(50);
  }else if (d_1 > 70 && d_2 <=70 && d_3 > 70 && d_4 > 10 && encendido){//izquierda
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
    lcd.setCursor(17, 2);
    lcd.print("=>");
    lcd.display();
    delay(100);
  }else if (d_1 > 70 && d_2 > 70 && d_3 <= 70 && d_4 > 10 && encendido){//izquierda
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
  lcd.setCursor(17, 2);
    lcd.print("=>");
    lcd.display();
    delay(100);
  }else if (d_1 <= 70 && d_2 <=70 && d_3 > 70 && d_4 > 10 && encendido){//derecha
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
    lcd.setCursor(17, 2);
    lcd.print("<=");
    lcd.display();
    delay(100);

  }else if (d_1 > 70 && d_2 <= 70 && d_3 <= 70 && d_4 > 10 && encendido){//izquierda 
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
  lcd.setCursor(17, 2);
    lcd.print("=>");
    lcd.display();
    delay(100);
  }else if(d_1 <= 70 && d_2 > 70 && d_3 <= 70 && d_4 > 10 && encendido){//izquierda
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
  lcd.setCursor(17, 2);
    lcd.print("=>");
    lcd.display();
    delay(100);
  }else if(d_1 > 70 && d_2 > 70 && d_3 > 70 && d_4 > 10 && encendido){//recta
  analogWrite(enA, velocidad);
  analogWrite(enB, velocidad);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
    lcd.setCursor(17, 2);
    lcd.print("|^|");
    lcd.display();
    delay(100);
  }
}

ISR(TIMER1_OVF_vect)                              //interrupcion del TIMER1 
{
  TCNT1 = 0xC2F7;                                 // Renicia TIMER
  segundos++;
  if(segundos == 60)
  {
    segundos = 0;
    minutos++;
  }
}
