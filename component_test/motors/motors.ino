/**
 * Pruebas relacionadas con el control de la dirección de giro de los motores
 */

#include <DefinicionPines.hpp>
#include <GiroMotores.hpp>


const int velocidad = 150;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  for (size_t i = 0; i < 4; ++i) {
    pinMode(pin::motor_enable[i], OUTPUT);
    pinMode(pin::motor_direction[i], OUTPUT);
  }
  for (int i = 2; i < 13; ++i) {
    pinMode(i, OUTPUT);
  }
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void girar_par_de_ruedas(int rueda1, int rueda2, int dir1, int dir2) {
  analogWrite(pin::motor_enable[rueda1], velocidad);
  digitalWrite(pin::motor_direction[rueda1], dir1);

  analogWrite(pin::motor_enable[rueda2], velocidad);
  digitalWrite(pin::motor_direction[rueda2], dir2);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  // Un sentido
  girar_par_de_ruedas(1, 3, HIGH, HIGH);
  girar_par_de_ruedas(0, 2, HIGH, HIGH);
  delay(5000);

  digitalWrite(LED_BUILTIN, HIGH);
  // Sentido contrario
  girar_par_de_ruedas(1, 3, LOW, LOW);
  girar_par_de_ruedas(0, 2, LOW, LOW);
  delay(5000);
}
