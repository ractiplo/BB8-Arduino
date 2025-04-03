#include <SoftwareSerial.h>  // Para la comunicaci�n con el Bluetooth

// Pines para el controlador L298N (ajusta seg�n tu conexi�n)
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define ENA 5
#define ENB 6

// Pines para el m�dulo Bluetooth HC-05
#define BT_RX 0  // Pin RX del HC-05 al pin 2 (TX del Arduino)
#define BT_TX 1  // Pin TX del HC-05 al pin 3 (RX del Arduino)

SoftwareSerial btSerial(BT_RX, BT_TX); // Crea el objeto SoftwareSerial

int velocidadMotor = 150; // Velocidad inicial (0-255)
char comando;             // Almacena el comando recibido

void setup() {
  Serial.begin(9600);   // Comunicaci�n serial con la computadora (opcional)
  btSerial.begin(9600); // Comunicaci�n serial con el Bluetooth

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

void loop() {
  // Revisa si hay datos desde Bluetooth
  if (btSerial.available() > 0) {
    comando = btSerial.read(); // Lee el comando
    Serial.println(comando); // Imprime el comando (para depuraci�n)

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
        //Podr�as a�adir case 'V': para cambiar la velocidad y luego leer otro caracter.
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



//Pasos Adicionales y Consideraciones:

//Conexi�n del Hardware:

//: Conecta los pines IN1, IN2, IN3, IN4, ENA y ENB del L298N a los pines correspondientes que definiste en el c�digo de Arduino. Conecta los motores a las salidas OUT1/OUT2 y OUT3/OUT4 del L298N. Aseg�rate de que el L298N tenga su propia fuente de alimentaci�n (la bater�a de tu BB-8) y que las tierras (GND) de Arduino y del L298N est�n conectadas.

//-05: Conecta VCC del HC-05 a 5V de Arduino, GND a GND, TXD a BT_RX (pin digital 2 en el c�digo), y RXD a BT_TX (pin digital 3 en el c�digo). Importante: El HC-05 funciona a 3.3V en sus pines de comunicaci�n, por lo que es muy recomendable usar un divisor de voltaje (con dos resistencias) en la l�nea RXD del HC-05 para bajar el voltaje de 5V de Arduino a 3.3V. Sin esto, podr�as da�ar el m�dulo Bluetooth.

// Mega: Aseg�rate de alimentar el Arduino Mega, ya sea por USB (para pruebas) o con una fuente externa.

//Aplicaci�n de Control en el Tel�fono

//Ajuste de la Velocidad:

//El c�digo establece una velocidad inicial (velocidadMotor = 150). Puedes modificar este valor (entre 0 y 255) para ajustar la velocidad m�xima. Puedes implementar el control de velocidad con comandos adicionales desde la aplicaci�n (como te suger� en la explicaci�n).

//Control de la Cabeza:

// c�digo se centra en el movimiento del cuerpo. El control de la cabeza, con los imanes, es independiente y no requiere c�digo. Si quisieras controlar la cabeza (por ejemplo, con un servomotor), tendr�as que agregar c�digo para eso y probablemente usar�as la biblioteca Servo.h.

//Mejoras (Opcional):

// de velocidad suave: Puedes implementar una aceleraci�n gradual en lugar de cambios bruscos de velocidad, para que el movimiento sea m�s suave.

//Feedback: Podr�as agregar sensores (como encoders en las ruedas) para obtener retroalimentaci�n de la posici�n y velocidad, y as� tener un control m�s preciso.

// de luces: Puedes agregar c�digo para controlar los LEDs, ya sea de forma manual (con comandos Bluetooth) o autom�tica (por ejemplo, que se enciendan al moverse).