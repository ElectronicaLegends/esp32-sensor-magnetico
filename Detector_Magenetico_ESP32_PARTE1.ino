/*
  Proyecto: Sensor magnético con ESP32
  Canal: Electrónica Legends

  Descripción:
  Detecta el estado de una puerta mediante un sensor magnético
  y controla el LED integrado del ESP32 según su estado.

  Funcionamiento:
  - Puerta abierta: LED encendido.
  - Puerta cerrada: LED apagado.
  - El estado de la puerta se muestra en el monitor serial.
*/

// Definición de los pines utilizados en el ESP32
#define Puerta 18       // GPIO 18 conectado al sensor magnético
#define LED_ESP32 2     // GPIO 2 asociado al LED integrado de la placa

void setup() {
  // Configura el GPIO 18 como entrada y activa la resistencia
  // interna pull-up para mantener estable la lectura del sensor.
  pinMode(Puerta, INPUT_PULLUP);

  // Configura el GPIO 2 como salida para controlar el LED.
  pinMode(LED_ESP32, OUTPUT);

  // Establece el LED inicialmente apagado (nivel lógico LOW).
  digitalWrite(LED_ESP32, LOW);

  // Inicia la comunicación serial a 115200 baudios
  // para visualizar los mensajes en el monitor serial.
  Serial.begin(115200);
}

void loop() {
  // Lee el estado lógico del sensor magnético.
  // Si el pin está en HIGH, PuertaAbierta será true.
  // Si el pin está en LOW, PuertaAbierta será false.
  // Esta lógica supone que HIGH corresponde a puerta abierta.
  bool PuertaAbierta = digitalRead(Puerta) == HIGH;

  // Comprueba si la puerta está abierta.
  if (PuertaAbierta)
  {
    // Si está abierta, enciende el LED.
    digitalWrite(LED_ESP32, HIGH);
  }
  else
  {
    // Si está cerrada, apaga el LED.
    digitalWrite(LED_ESP32, LOW);
  }

  // Imprime el texto "Puerta: " en el monitor serial.
  Serial.print("Puerta: ");

  // Muestra "ABIERTA" si PuertaAbierta es true
  // o "CERRADA" si es false.
  // El operador ?: permite seleccionar entre dos valores.
  Serial.println(PuertaAbierta ? "ABIERTA" : "CERRADA");

  // Espera 100 milisegundos antes de repetir el ciclo.
  // Esto limita la frecuencia de lectura y de impresión.
  delay(100);
}