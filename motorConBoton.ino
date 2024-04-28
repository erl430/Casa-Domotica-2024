int motor = 6;   // variables
int boton = 8;

void setup() {
  pinMode(motor, OUTPUT);  // Asignamos el pin asociado al botón como pin de salida
  pinMode(boton, INPUT);   // Asignamos el pin asociado al botón como pin de entrada
  Serial.begin(9600);      // Habilita el puerto serie a 9600
}

void loop() {
  if (digitalRead(boton) == 1) {             // Si el botón está pulsado
    Serial.println("se pulsa el boton");     // Imprimimos por pantalla mensaje de comprobación
    analogWrite(motor, 0);                   // Se pone en marcha el motor
    
    delay(3000);                             // Espera de 3 segundos

    analogWrite(motor, 250);                 // Se para el motor
  }
}
