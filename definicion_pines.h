#pragma once
#include <Arduino.h>
namespace pin {
  const int motor_enable[] = { 8, 9, 10, 11 };
  const int motor_direction[] = { 40, 41, 42, 43 };
  const int encoder_outA[] = { 30, 32, 34, 36 };
  const int encoder_outB[] = { 31, 33, 35, 37 };

  const int ldr[] = { A0, A1, A2, A3 };
  const int infra[] = { A4, A5, A6, A7 };
  const int ultra_trig[] = { 22, 24, 26 };
  const int ultra_echo[] = { 23, 25, 27 };
}
