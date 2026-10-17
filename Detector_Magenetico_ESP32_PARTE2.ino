
/*
  Proyecto: Sensor magnético con ESP32
  Canal: Electrónica Legends
  Proyecto 01 - Parte 2

  Descripción:
  Detecta la apertura y el cierre de una puerta mediante
  un sensor magnético, controla el LED integrado del ESP32
  y establece una conexión con una red WiFi.

  Funcionamiento:
  - Puerta abierta: LED encendido.
  - Puerta cerrada: LED apagado.
  - El estado se muestra en el monitor serial únicamente
    cuando se detecta un cambio.
  - El ESP32 se conecta a una red WiFi.
*/

// Librería para gestionar la conexión WiFi del ESP32
#include <WiFi.h>

// Definición de los pines utilizados en el ESP32
#define Puerta 18       // GPIO 18 conectado al sensor magnético
#define LED_ESP32 2     // GPIO 2 asociado al LED integrado

// Credenciales de la red WiFi
const char* ssid = "NOMBRE_DE_TU_WIFI";
const char* password = "CONTRASENA_DE_TU_WIFI";

// Variable para almacenar el último estado conocido de la puerta
bool ultimoEstado;

void setup() {
  // Configura el sensor como entrada con resistencia pull-up
  pinMode(Puerta, INPUT_PULLUP);

  // Configura el LED como salida
  pinMode(LED_ESP32, OUTPUT);

  // Inicia la comunicación serial
  Serial.begin(115200);

  // Lee el estado inicial del sensor
  ultimoEstado = digitalRead(Puerta) == HIGH;

  // Sincroniza el LED con el estado inicial de la puerta
  digitalWrite(LED_ESP32, ultimoEstado ? HIGH : LOW);

  // Muestra el estado inicial una sola vez
  Serial.print("Estado inicial de la puerta: ");
  Serial.println(ultimoEstado ? "ABIERTA" : "CERRADA");

  // Inicia la conexión a la red WiFi
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);

  // Espera hasta que el ESP32 se conecte a la red
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Informa que la conexión se estableció correctamente
  Serial.println();
  Serial.println("WiFi conectado correctamente.");

  // Muestra la dirección IP asignada al ESP32
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Lee el estado actual del sensor magnético
  bool PuertaAbierta = digitalRead(Puerta) == HIGH;

  // Comprueba si el estado actual es diferente al anterior
  if (PuertaAbierta != ultimoEstado) {

    // Actualiza el estado del LED según la puerta
    digitalWrite(LED_ESP32, PuertaAbierta ? HIGH : LOW);

    // Muestra el nuevo estado únicamente cuando hay un cambio
    Serial.print("Puerta: ");
    Serial.println(PuertaAbierta ? "ABIERTA" : "CERRADA");

    // Guarda el estado actual para compararlo en la próxima lectura
    ultimoEstado = PuertaAbierta;
  }

  // Pequeña pausa antes de volver a leer el sensor
  delay(50);
}
