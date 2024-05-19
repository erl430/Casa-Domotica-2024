// LIBRERIAS
#include <SoftwareSerial.h>  // Incluimos la librería SoftwareSerial
#include <Servo.h>           // Incluimos la librería de control de Servo

SoftwareSerial BT(10, 11);  // Definimos los pines RX y TX del Arduino conectados al Bluetooth

// VARIABLES
int c;                        // variable para guardar el valor que nos manda el dispositivo bluetooth
bool alarmaActivada = false;  // estado de la alarma, inicializado a falso

// pines asociados a cada dispositivo
int led1 = 8;
int led2 = 2;
int led3 = 4;
int motor = 12;
int pulsador = 3;
int zumbador = 7;
int pinServo = 9;  // numero de pin del servo

// sensor de distancia
int trig = 6;
int echo = 5;

Servo servo_13;    // Servo

void setup() {
  BT.begin(9600);
  servo_13.attach(pinServo);  // Asocia el servo al pin
  Serial.begin(9600);         // Inicializamos  el puerto serie

  pinMode(led1,OUTPUT);       // Inicializamos cada pin como entrada/salida
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(pulsador,INPUT);
  pinMode(zumbador,OUTPUT);
  pinMode(pinServo,OUTPUT);
  pinMode(A1,INPUT);
}

void loop() {
  // Comprueba si está la alarma activada, y si hay algo cerca. Si lo hay, suena la alarma
  hayAlgoCerca();

  // Comprueba si el botón está pulsado. Si lo está, enciende el motor
  botonPulsado();

  // Comprueba si hay luz ambiental, para apagar o encender las luces
  hayLuz();

  if (BT.available())  // Si llega un dato por el puerto BT se envía al monitor serial
  {
    c = BT.read();  // guardamos en la variable el valor leido

    switch (c) {
      case 254:  // se pulsa luces de jardín on
        Serial.println("Se encienden las luces de jardín");
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(led3, HIGH);
        break;
      case 255:  // se pulsa luces de jardín off
        Serial.println("Se apagan las luces de jardín");
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        break;
      case 243:  // se pulsa abrir puerta
        Serial.println("Se abre la puerta");
        servo_13.write(60);
        break;
      case 247:  // se pulsa cerrar puerta
        Serial.println("Se cierra la puerta");
        servo_13.write(5);
        break;
      case 231:  // se activa la alarma
        Serial.println("Se activa la alarma");
        alarmaActivada = true;
        break;
      case 250:  // se desactiva la alarma
        Serial.println("Se desactiva la alarma");
        alarmaActivada = false;
        break;
      case 218:  // se pulsa apagar el sonido de la alarma
        Serial.println("Se apaga el sonido de la alarma");
        noTone(zumbador);
        break;
      case 222:  // se activa el simulador de viento
        digitalWrite(motor, LOW);
        Serial.println("Se activa el simulador de viento");
        break;
      case 223:  // se desactiva el simulador de viento
        digitalWrite(motor, HIGH);
        Serial.println("Se desactiva el simulador de viento");
        break;
      default:   // si llega cualquier valor no esperado, no hace nada
        Serial.println("Nada");
        break;
    }
  }
}

// FUNCIONES ADICIONALES

/*
 * Calcula y retorna la distancia a la que el sensor detecta un objeto
 */
long calculaDistanciaAlarma(int triggerPin, int echoPin) {
  // Limpia los valores del ultrasonido, por si acaso
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // El trigger manda una señal durante 10 microsegundos
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // Lee el valor de la señal del pin echo y devuelve el tiempo en microsegundos
  return pulseIn(echoPin, HIGH);
}

/*
 * Si detecta que hay algo cerca, y la alarma está activada, suena el zumbador
 */
void hayAlgoCerca() {
  if (alarmaActivada == true) {   // Si la alarma está activada
    if (0.01723 * calculaDistanciaAlarma(trig, echo) < 20) {  // Si la distancia es menor a 20
      tone(zumbador, 1000);
      Serial.println(0.01723 * calculaDistanciaAlarma(trig, echo));
    } else {
      noTone(zumbador);
    }
  } else {                       // Si la alarma no está activada
    noTone(zumbador);
  }
}

/*
 * Si el botón está pulsado, se pone el motor activo 3 segundos
 */
void botonPulsado() {
  // si se pulsa el boton, se pone el motor activo 3 segundos
  if (digitalRead(pulsador) == 1) {
    digitalWrite(motor, LOW); // se enciende el motor
    delay(3000);
    digitalWrite(motor, HIGH); // se apaga el motor
  } 
}

/*
 * Comprueba el nivel de luz ambiental. Si es bajo, enciende las luces y si no, las apaga
 */
void hayLuz() {
  if (analogRead(A1) < 900) {  // Si hay suficiente luz ambiental, se apagan las luces
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  } else {  // Si no, se apagan
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
  Serial.println(analogRead(A1));
  delay(1000);
}
