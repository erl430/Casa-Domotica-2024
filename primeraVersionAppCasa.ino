#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth

int c;                    // variable para guardar el valor que nos manda el dispositivo bluetooth
bool alarmaActivada = false; // estado de la alarma, inicializado a falso

void setup()
{
  BT.begin(9600);       // Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);   // Inicializamos  el puerto serie  
}

void loop()
{
  if(BT.available())                 // Si llega un dato por el puerto BT se envía al monitor serial
  {
    c = BT.read();                   // guardamos en la variable el valor leido

    switch (c) {
      case 254:  // se pulsa luces de jardín on
        Serial.println("Se encienden las luces de jardín");
        break;
      case 255:  // se pulsa luces de jardín off
        Serial.println("Se apagan las luces de jardín");
        break;
      case 243:  // se pulsa abrir puerta 
        Serial.println("Se abre la puerta");
        break;
      case 247:  // se pulsa cerrar puerta 
        Serial.println("Se cierra la puerta");
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
        break;
      case 222:  // se activa el simulador de viento
        Serial.println("Se activa el simulador de viento");
        break;
      case 223:  // se desactiva el simulador de viento
        Serial.println("Se desactiva el simulador de viento");  
        break;
      default:
        Serial.println("Nada");
        break;
    }
  }
 
 /**
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
    Serial.println("Serial available");
     BT.write(Serial.read());
     Serial.println("Serial: " +Serial.read());
  }
  **/
}
