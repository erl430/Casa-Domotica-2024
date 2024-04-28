int motor = 6;   // variables

void setup() {
  pinMode(motor, OUTPUT);  // Asignamos el pin asociado al motor como pin de salida
  Serial.begin(9600);      // Habilita el puerto serie a 9600
}

void loop() {
    analogWrite(motor, 0);    // Salida del motor a 0
    delay(3000);              // Espera de 3 segundos

    analogWrite(motor, 250);  // Salida del motor a 250
    delay(3000);              // Espera de 3 segundos

}
