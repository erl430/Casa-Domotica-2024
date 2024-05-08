#include <Servo.h>
#include <SoftwareSerial.h>  // Incluimos la librería  SoftwareSerial
SoftwareSerial BT(10, 11);   // Definimos los pines RX y TX del Arduino conectados al Bluetooth

int c;                        // variable para guardar el valor que nos manda el dispositivo bluetooth
bool alarmaActivada = false;  // estado de la alarma, inicializado a falso

// variables de dispositivos conectados a la placa
// CAMBIAR NÚMEROS POR SU PIN CORRESPONDIENTE
int led1 = 0;
int led2 = 0;
int led3 = 0;
int motor = 0;
int pulsador = 0;
int zumbador = 0;
int servo = 0;  // numero de pin del servo

// sensor de distancia
int trig = 0;
int echo = 0;

Servo servoPuerta;  // Servo

void setup() {
  BT.begin(9600);      // Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);  // Inicializamos  el puerto serie

  // Inicializamos pines como salidas y entradas
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(pulsador, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(zumbador, OUTPUT);
  // sensor de luz
  pinMode(A0, INPUT);
  // servo
  servoPuerta.attach(servo);
}

void loop() {

  // Comprueba si está la alarma activada, y si hay algo cerca. Si lo hay, suena la alarma
  hayAlgoCerca();

  // Comprueba si el botón está pulsado
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
        servoPuerta.write(75);  // hay que valorar qué ángulo
        break;
      case 247:  // se pulsa cerrar puerta
        Serial.println("Se cierra la puerta");
        servoPuerta.write(5);  // hay que valorar qué ángulo
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
        digitalWrite(zumbador, LOW);
        break;
      case 222:  // se activa el simulador de viento
        Serial.println("Se activa el simulador de viento");
        digitalWrite(motor, HIGH);
        break;
      case 223:  // se desactiva el simulador de viento
        Serial.println("Se desactiva el simulador de viento");
        digitalWrite(motor, LOW);
        break;
      default:
        Serial.println("Nada");
        break;
    }
  }
}

// Funciones adicionales

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
  if (alarmaActivada == true) {
    if (0.01723 * calculaDistanciaAlarma(trig, echo) < 80) {  // Si la distancia es menor a 80
      digitalWrite(zumbador, HIGH);
      Serial.println(0.01723 * calculaDistanciaAlarma(trig, echo));
    } else {
      digitalWrite(5, LOW);
    }
  }
}

/*
 * Si el botón está pulsado, se pone el motor activo 3 segundos
 */
void botonPulsado() {
  // si se pulsa el boton, se pone el motor en activo 3 segundos
  if (digitalRead(pulsador) == 1) {
    digitalWrite(7, HIGH);
    delay(3000);  
    digitalWrite(7, LOW);
  }
}

/*
 * Comprueba el nivel de luz ambiental. Si es bajo, enciende las luces y si no, las apaga
 */
void hayLuz() {
  if (analogRead(A0) < 700) {    // Si hay suficiente luz ambiental, se apagan las luces
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
  } else {                       // Si no, se apagan
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
  }
}
