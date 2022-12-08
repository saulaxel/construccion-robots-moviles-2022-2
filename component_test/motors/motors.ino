/**
 * Pruebas relacionadas con el control de la dirección de giro de los motores
 */

#include <DefinicionPines.h>

const int velocidad = 100;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  for (size_t i = 0; i < 4; ++i) {
    pinMode(pin::motor_enable[i], OUTPUT);
    pinMode(pin::motor_direction[i], OUTPUT);
  }
}

void girar_par_de_ruedas(int rueda1, int rueda2, int dir1, int dir2) {
  analogWrite(pin::motor_enable[rueda1], velocidad);
  digitalWrite(pin::motor_direction[rueda1], dir1);

  analogWrite(pin::motor_enable[rueda2], velocidad);
  digitalWrite(pin::motor_direction[rueda2], dir2);
}

#define PROBAR_AVANCE 1
#define PROBAR_GIRO   1

void loop() {
  #ifdef PROBAR_AVANCE
  digitalWrite(LED_BUILTIN, LOW);
  // Primer par de ruedas, un sentido
  girar_par_de_ruedas(1, 3, HIGH, LOW);
  delay(5000);

  // Primer par de ruedas, sentido contrario
  girar_par_de_ruedas(1, 3, LOW, HIGH);
  delay(5000);

  // Segundo par de ruedas, un sentido
  girar_par_de_ruedas(0, 2, HIGH, LOW);
  delay(5000);

  // Segundo par de ruedas, sentido contrario
  girar_par_de_ruedas(0, 2, LOW, HIGH);
  delay(5000);

  #endif

  #ifdef PROBAR_GIRO
  digitalWrite(LED_BUILTIN, HIGH);
  // Primer par de ruedas, un sentido
  girar_par_de_ruedas(1, 3, HIGH, HIGH);
  delay(5000);

  // Primer par de ruedas, sentido contrario
  girar_par_de_ruedas(1, 3, LOW, LOW);
  delay(5000);

  // Segundo par de ruedas, un sentido
  girar_par_de_ruedas(0, 2, HIGH, HIGH);
  delay(5000);

  // Segundo par de ruedas, sentido contrario
  girar_par_de_ruedas(0, 2, LOW, LOW);
  delay(5000);
  #endif
}
