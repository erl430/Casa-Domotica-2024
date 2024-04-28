// variables
int led = 8;

void setup()
{
  pinMode(A1, INPUT);    // inicializamos sensor de luz como pin de entrada
  pinMode(led, OUTPUT);    // inicializamos led como pin de salida
  Serial.begin(9600);
}

void loop()
{
  if (analogRead(A1) < 700) {               // si el sensor tiene un valor inferior a 700 (detecta mucha luz) 
    digitalWrite(led, LOW);                        // las luces se apagan
    Serial.println("se apagan las luces");
  } else {
    digitalWrite(led, HIGH);                       // y si no, las luces se encienden
    Serial.println("se encienden las luces");
  }
  Serial.println(analogRead(A1));                   // imprime por pantalla el valor del sensor de luz
  delay(1000);                                      // espera de 1 segundo
}
