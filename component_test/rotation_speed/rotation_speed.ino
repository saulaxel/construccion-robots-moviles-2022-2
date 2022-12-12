#include <DefinicionPines.hpp>

void setup() {
  for (size_t i = 0; i < 4; ++i) {
    pinMode(pin::motor_enable[i], OUTPUT);
    pinMode(pin::motor_direction[i], OUTPUT);
  }
}

void girar_par_de_ruedas(int velocidad, int rueda1, int rueda2, int dir1, int dir2) {
  analogWrite(pin::motor_enable[rueda1], velocidad);
  digitalWrite(pin::motor_direction[rueda1], dir1);

  analogWrite(pin::motor_enable[rueda2], velocidad);
  digitalWrite(pin::motor_direction[rueda2], dir2);
}

int velocidad = 0;
void loop() {
  girar_par_de_ruedas(velocidad, 1, 3, HIGH, HIGH);
  girar_par_de_ruedas(velocidad, 0, 2, HIGH, HIGH);
  delay(500);
  if (velocidad == 0) {
    delay(2500); // Un delay extra en cada que la velocidad se reinicie
  }

  // Se irá incrementando la velocidad progresivamente
  velocidad += 5;

  if (velocidad > 255) {
    velocidad = 0;
  }
}
