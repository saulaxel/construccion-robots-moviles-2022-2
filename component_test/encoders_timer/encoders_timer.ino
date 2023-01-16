/*
   Prueba de los encoders usando timers
*/

#include <DefinicionPines.hpp>
#include <GiroMotores.hpp>
#include <Encoder.h>
#include <TimerOne.h>

const int rueda_prueba = 0;
const int velocidad = 100;

// Objetos para leer la posición del encoder
void leer_encoder(void);
volatile int posEncoder = 0;

Encoder enc(pin::encoder_A[rueda_prueba], pin::encoder_B[rueda_prueba]);

void setup() {
  Serial.begin(115200);
  // Para controlar el motor se configura un pin PWM y uno digital como salida
  pinMode(pin::motor_enable[rueda_prueba], OUTPUT);
  pinMode(pin::motor_direction[rueda_prueba], OUTPUT);

  // Para el encoder, se configuran dos pines digitales como entrada
  pinMode(pin::encoder_A[rueda_prueba], INPUT);
  pinMode(pin::encoder_B[rueda_prueba], INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  // El timer que se encargará de leer el encoder 10,000 veces por segundo.
  // 1,000 veces por segundo son visiblemente insuficientes pues la gráfica
  // todavía no se corresponde con una línea, por lo que el siguiente
  // initialize debe llebar un número por lo menos menor a 1,000 micros
  Timer1.initialize(100);
  Timer1.attachInterrupt(leer_encoder);
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

  Serial.print(A); Serial.print(" ");
  Serial.print(B); Serial.print(" ");
  Serial.println(posEncoder / 100.0 + 2);

  delay(10);
}

void leer_encoder(void) {
  posEncoder = enc.read();
}
