// Definiciones de pines
#define BT_RX 2  // Pin RX del HC-05 al pin 2 (TX del Arduino)
#define BT_TX 3  // Pin TX del HC-05 al pin 3 (RX del Arduino)

// Pines del motor (Definir pines correctos segun conexionado)
#define IN1 8  
#define IN2 9  
#define IN3 10 
#define IN4 11 
#define ENA 5  
#define ENB 6  

// Librerías
#include <SoftwareSerial.h>

// Creación de objetos
SoftwareSerial btSerial(BT_RX, BT_TX); // Crea el objeto SoftwareSerial

// Variables globales
int velocidadMotor = 150; // Velocidad inicial (0-255)
char comando;             // Almacena el comando recibido

// Función de configuración (se ejecuta una vez al inicio)
void setup() {
  Serial.begin(9600);   // Comunicación serial con la computadora (opcional)
  btSerial.begin(9600); // Comunicación serial con el Bluetooth

  // Configura los pines del motor como salidas
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  analogWrite(ENA, velocidadMotor);  // Estable velocidad inicial
  analogWrite(ENB, velocidadMotor);
}

// Función principal (se ejecuta repetidamente)
void loop() {
  // Revisa si hay datos desde Bluetooth
  if (btSerial.available() > 0) {
    comando = btSerial.read(); // Lee el comando
    Serial.println(comando);    // Imprime el comando (para depuración)

    // Interpreta el comando
    switch (comando) {
      case 'F':
        avanzar();
        break;
      case 'B':
        retroceder();
        break;
      case 'L':
        girarIzquierda();
        break;
      case 'R':
        girarDerecha();
        break;
      case 'S':
        detener();
        break;
        // Podrías añadir case 'V': para cambiar la velocidad y luego leer otro caracter.
    }
  }
}

// Funciones para controlar los motores
void avanzar() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void retroceder() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void girarIzquierda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void girarDerecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void detener() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
