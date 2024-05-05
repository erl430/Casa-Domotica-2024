// Función que se encarga de la lectura de datos del sensor
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);          // Pin trigger como salida
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);       // Pin trigger manda señal durante 10 microsegundos
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);        // Pin trigger deja de mandar señal
  pinMode(echoPin, INPUT);              // Pin echo como entrada
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);       // Lee el valor del pin echo y devuelve el tiempo tardado
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("Lectura de datos: ");
  Serial.println(0.01723 * readUltrasonicDistance(6, 5));   // Llama a la función creada arriba, con los valores de los pines Trig y Echo, y convierte el valor a centímetros. Lo imprime por pantalla
  delay(1000); // Wait for 1000 millisecond(s)
}
