/*
   Prueba de los encoders
*/

#include <DefinicionPines.hpp>
#include <GiroMotores.hpp>
#include <Encoder.h>

const int rueda_prueba = 0;
const int velocidad = 100;

Encoder enc(pin::encoder_A[rueda_prueba], pin::encoder_B[rueda_prueba]);

void setup() {
  Serial.begin(9600);
  // Para controlar el motor se configura un pin PWM y uno digital como salida
  pinMode(pin::motor_enable[rueda_prueba], OUTPUT);
  pinMode(pin::motor_direction[rueda_prueba], OUTPUT);

  // Para el encoder, se configuran dos pines digitales como entrada
  pinMode(pin::encoder_A[rueda_prueba], INPUT);
  pinMode(pin::encoder_B[rueda_prueba], INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

// Se quiere alternar entre varios estados usando el contador
// Contador entre 0 y 999: La rueda gira en una dirección
// Contador entre 1000 y 1999: La rueda se detiene
// Contador entre 2000 y 2999: La rueda gira en la otra dirección
// Contador entre 3000 y 3999: La rueda se detiene

int contador = 0;
void loop() {

  if (contador == 0) {
    turn_wheel(rueda_prueba, clockwise, velocidad);
  }
  else if (contador == 1000) {
    stop_wheel(rueda_prueba);
  }
  else if (contador == 2000) {
    turn_wheel(rueda_prueba, anticlockwise, velocidad);
  }
  else if (contador == 3000) {
    stop_wheel(rueda_prueba);
  }
  
  
  contador = (contador + 1) % 4000;

  // Valores lógicos leidos directo del encoder, sin procesar por Encoder.h
  int A = digitalRead(pin::encoder_A[rueda_prueba]);
  int B = digitalRead(pin::encoder_B[rueda_prueba]);
  // Valor de Encoder.h, procesado para contar avance
  int posEncoder = enc.read();

  Serial.print(A); Serial.print(" ");
  Serial.print(B); Serial.print(" ");
  Serial.println(posEncoder / 100.0 + 2);
}
