#include <DefinicionPines.hpp>

void setup() {
  for (size_t i = 0; i < 4; ++i) {
    pinMode(pin::motor_enable[i], OUTPUT);
    //pinMode(pin::motor_direction[i], OUTPUT);
    // Si el enable está permanentemente en bajo, no deherbía haber movimiento
    digitalWrite(pin::motor_enable[i], LOW);
    //digitalWrite(pin::motor_direction[i], LOW);
  }
}

void loop() {
}
