#pragma once
#include <Arduino.h>

// Constantes arbitrarias para identificar la dirección
// El orden de declaración importa, pues al primer valor de una enumeración
// se le asigna el valor 0 y al segundo se le asigna 1
enum Direction {
  clockwise,
  anticlockwise,
};

// Arreglo con la intención de indicar que voltaje representa un giro horario
// de la rueda y que voltaje representa un giro anti-horario.
//
// Por ejemplo, el primer valor indica que para la rueda 0, HIGH hace girar
// la rueda en sentido horario y LOW la hace girar en sentido contrario
int dir_to_weel_voltage[][2] = {
    [0] = { [clockwise] = HIGH, [anticlockwise] = LOW  },
    [1] = { [clockwise] = LOW , [anticlockwise] = HIGH },
    [2] = { [clockwise] = LOW , [anticlockwise] = HIGH },
    [3] = { [clockwise] = HIGH, [anticlockwise] = LOW  },
};

/*
 * Gira una rueda.
 * 'wheel' es el número de rueda, de 0 a n-1, siendo n el número de ruedas
 *         del robot
 * 'dir' puede ser clockwise o anticlockwise. Para que gire adecuadamente,
 *         es necesario que los valores del arreglo dir_to_weel_voltage sean
 *         apropiados para la forma en que está alambrado el robot.
 * 'speed' es el ciclo de trabajo de PWM, va de 0 a 255
 */
inline void turn_wheel(int wheel, Direction dir, int speed) {
  analogWrite(pin::motor_enable[wheel], speed);
  digitalWrite(pin::motor_direction[wheel], dir_to_weel_voltage[wheel][dir]);
}

/*
 * Para la rueda indicada
 * 'wheel' es el número de rueda, de 0 a n-1
 */
inline void stop_wheel(int wheel) {
    analogWrite(pin::motor_enable[wheel], 0);
}
