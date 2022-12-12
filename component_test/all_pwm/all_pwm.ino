/**
 * Pruebas relacionadas con el control de la dirección de giro de los motores
 */

#include <DefinicionPines.hpp>
#include <GiroMotores.hpp>


const int velocidad = 150;

void setup() {
  for (size_t i = 0; i < 4; ++i) {
    pinMode(pin::motor_direction[i], OUTPUT);
  }
  for (int i = 2; i < 13; ++i) {
    pinMode(i, OUTPUT);
  }
  for (int i = 2; i < 13; ++i) {
      analogWrite(i, velocidad);
  }
}

void loop() {
  // Un sentido
  for (int i = 40; i < 44; ++i) {
    digitalWrite(i, LOW);
  }
  delay(5000);

  for (int i = 40; i < 44; ++i) {
    digitalWrite(i, HIGH);
  }
  delay(5000);
}
