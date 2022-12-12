# Pruebas 11/12/2022

## zero_speed

### Resultado esperado

Las ruedas no deberían moverse

### Resultado obtenido

Dos ruedas siempre giran incluso cuando se manda una señal _LOW_ a sus
enables o un PWM con ciclo de trabajo cero.

Se detiene el movimiento cuando no se habilitan los pines de dirección para
salida, tal como se observó en la prueba __zero_speed_disable_direction__, en
la cual se comentaron las instrucciones pinMode(_, OUTPUT) correspondientes a
los enable.

Dado que un par de pines tuvieron que cambiarse respecto al modelo original,
se quiere descartar que este comportamiento sea causado por un uso de números
de pin incorrectos en el código. Mediante experimentos como los usados en
__all_pwm/__, se corroboró que incluso enviando _LOW_ por todos los pines
que disponen de PWM, el comportamiento anormal continua, por lo que el cambio
de pines no parece ser el origen del problema.

## motors

### Resultado esperado

Las cuatro ruedas deberían girar en al mismo tiempo durante un periodo
concreto. Tras pasar dicho periodo, la dirección de giro se debe invertir.

### Resultado obtenido

Tres ruedas giran cuando se intentan girar las cuatro. La dirección gira
adecuadamente en dichas 3 ruedas.

## rotation_speed/

### Resultado esperado

Empezando desde el reposo, la velocidad de giro de todas las ruedas tiene que
aumentar paulatinamente hasta llegar mediante la modificación del ciclo de
trabajo hasta alcanzar una velocidad máxima. Una vez alcanzada dicha
velocidad pico tendrá que haber una pausa moderada, tras lo cual se repetirá
el proceso.

### Resultado obtenido

El control de velocidad solo parece funcionar en una rueda.

En cuanto al resto de ruedas, la que no se movía sigue mostrando este
comportamiento. Las ruedas cuyo movimiento no se pudo detener mediante la
prueba __zero_speed__ aparentemente tampoco permiten modificar la velocidad.
