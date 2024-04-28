String sensorLuz = "A0";  // variables
int led = 8;

void setup()
{
  pinMode(sensorLuz, INPUT);    // inicializamos sensor de luz como pin de entrada
  pinMode(led, OUTPUT);    // inicializamos led como pin de salida
  Serial.begin(9600);
}

void loop()
{
  if (analogRead(sensorLuz) < 700) {               // si el sensor tiene un valor inferior a 700 (detecta mucha luz) 
    digitalWrite(led, LOW);                        // las luces se apagan
  } else {
    digitalWrite(led, HIGH);                       // y si no, las luces se encienden
  }
  Serial.println(analogRead(A0));                   // imprime por pantalla el valor del sensor de luz
  delay(1000);                                      // espera de 1 segundo
}
