/************************************************************************
 * Algoritmo de Evasión de Obstaculos                                   *
 * Programa en C de Arduino para un robot móvil que evade               *
 * obstáculos.                                                          *
 * Lab. Bio-Robótica                                                    *
 * FI-UNAM                                                              *
 *                                                                      *
 ************************************************************************/

// ######################### Macros #########################

#define motor_tiene_encoders true

#define TAM_ARRAY(arr) (sizeof(arr) / sizeof(*(arr)))

#define ADELANTE move_robot(AVANCE, 0.0f)
#define ATRAS move_robot(-AVANCE, 0.0)
#define GIRO_IZQ move_robot(0.0, GIRO)
#define GIRO_DER move_robot(0.0, -GIRO)
#define ALTO move_robot(0.0,0.0)

// ######################### Periféricos #########################

// Pines
#include <DefinicionPines.h>

// Auxiliares para el motor
enum Direction {
  clockwise,
  anticlockwise,
};

#ifndef motor_tiene_encoders
const int ciclo_trabajo = 50;
const float velocidad_avance = .5;
const float velocidad_giro = 1;
#endif // NOT motor_tiene_encoders

enum motor {
  motor_up,
  motor_right,
  motor_down,
  motor_left,
  num_motors // Cantidad de motores
};

// Auxiliares para los encoders del motor
#ifdef motor_tiene_encoders
const float diametro_rueda = 3.8; // Medida en centímetros
const int pulsos_por_revolucion = 12;
inline float distancia(int pulsos) {
  float revol = (float)pulsos / pulsos_por_revolucion;
  float dist = revol * PI * diametro_rueda;
  return dist;
}
#endif // motor_tiene_encoders

// La cantidad que hay de cada tipo de sensor
const size_t num_ldrs = TAM_ARRAY(pin::ldr);
const size_t num_infras = TAM_ARRAY(pin::infra);
const size_t num_ultras = TAM_ARRAY(pin::ultra_trig);

// Auxiliares para el ultrasónico
const float centimetros_por_microsegundo = (1.0f / 29.2f);
const long umbral_ultra = 15;


// ####

// Configuración de los pines de entrada y salida
void setup() {
  Serial.begin(9600); // Inicializa comunicación serial
  using namespace pin;
  //Configuración de los motores
  for (size_t i = 0; i < num_motors; ++i) {
    pinMode(motor_enable[i], OUTPUT);
    pinMode(motor_direction[i], OUTPUT);
    pinMode(encoder_outA[i], INPUT);
    pinMode(encoder_outB[i], INPUT);
  }


  //Configuración de los sensores de entrada
  for (auto pin_ldr : pin::ldr) {
    pinMode(pin_ldr, INPUT);
  }

  for (auto pin_infra : pin::infra) {
    pinMode(pin_infra, INPUT);
  }

  for (size_t i = 0; i < num_ultras; ++i) {
    pinMode(ultra_trig[i], OUTPUT);
    pinMode(ultra_echo[i], INPUT);
  }
}

void setMotorDirection(int index, Direction d)
{
  if (d == clockwise) {
    digitalWrite(pin::motor_direction[index], HIGH);
  } else {
    digitalWrite(pin::motor_direction[index], LOW);
  }
}

void setMotorSpeed(int index, int motorSpeed)
{
  analogWrite(pin::motor_enable[index], motorSpeed);
}

#ifndef motor_tiene_encoders
void avance_robot(float distancia)
{
  setMotorSpeed(motor_left, ciclo_trabajo);
  setMotorSpeed(motor_right, ciclo_trabajo);
  if (distancia > 0) {
    setMotorDirection(motor_left, clockwise);
    setMotorDirection(motor_right, anticlockwise);
  } else {
    setMotorDirection(motor_left, anticlockwise);
    setMotorDirection(motor_right, clockwise);
  }
  delay(distancia * velocidad_avance);
  digitalWrite(motor_left, LOW);
  digitalWrite(motor_right, LOW);
}

void giro_robot(float angulo)
{
  for (size_t m = 0; m < num_motors; ++m) {
    setMotorSpeed(m, ciclo_trabajo);
    if (angulo > 0) {
      setMotorDirection(m, clockwise);
    } else {
      setMotorDirection(m, anticlockwise);
    }
  }
  
  delay(angulo * velocidad_giro);

  for (size_t m = 0; m < num_motors; ++m) {
    digitalWrite(m, LOW);
  }  
}
#else // SI motor_tiene_encoders
void avance_robot(float distancia)
{
  
}

void giro_robot(float angulo)
{
  
}
#endif // motor_tiene_encoders

long leer_ultra(int index) {  
  long tiempo_ir_regresar_us, tiempo_ida_us;
  long distancia_cm = leer_ultra(index);
  
  // Indicar al sensor ultrasónico que envíe una onda de sonido
  digitalWrite(pin::ultra_trig[index], LOW);
  delayMicroseconds(4);
  digitalWrite(pin::ultra_trig[index], HIGH);
  delayMicroseconds(10);
  digitalWrite(pin::ultra_trig[index], LOW);  

  // Leemos de Echo el tiempo que tarda la onda en regresar
  tiempo_ir_regresar_us = pulseIn(pin::ultra_echo[index], HIGH);
  tiempo_ida_us = tiempo_ir_regresar_us / 2;

  distancia_cm = tiempo_ida_us * centimetros_por_microsegundo;

  return distancia_cm;
}

// Esta función lee el valor de un sensor, indicando su tipo y numero, y regresa su valor
float shs(String sensor, int num_sensor)
{
  float x=1.0;

  if (sensor == "ultra") {
    long distancia_cm = leer_ultra(num_sensor);
    if (distancia_cm < umbral_ultra) {
      x = 0;
    }
  }
  
  return(x);
}

void move_robot(float distancia, float angulo)
{
  avance_robot(distancia);
  giro_robot(angulo);
}

// Algoritmo de evasión de obstáculos
void loop()
{
  int estado = 0;
  float Si, Sm, Sd;
  float AVANCE =.1;
  float GIRO = 0.7854;
  // Estado inicial
  estado = 0;
  // Loop infinito
  while (1){
    // Se leen los sensores
    Si = shs("ultra", 0);
    Sm = shs("ultra", 1);
    Sd = shs("ultra", 2);
    
    Serial.print("Estado Presente: ");
    Serial.println(estado);
    Serial.print("Si: ");
    Serial.println(Si);
    Serial.print("Sd: ");
    Serial.println(Sd);
    switch (estado){
      case 0: // est0
        if (Si == 0){
          if (Sd == 0){
            estado = 0;
            ADELANTE;
            Serial.println("ADELANTE");
          }
          else{
            estado = 1;
            ALTO;
            Serial.println("ALTO");
          }
        }
        else{
          if (Sd == 0){
            estado = 3;
            ALTO;
            Serial.println("ALTO");
          }
          else{
            estado = 5;
            ALTO;
            Serial.println("ALTO");
          }
        }
        break;
      case 1: // est1
        estado = 2;
        ATRAS;
        Serial.println("ATRAS");
        break;
      case 2: // est2
        estado = 0;
        GIRO_IZQ;
        Serial.println("GIRO_IZQ");
        break;
      case 3: // est3
        estado = 4;
        ATRAS;
        Serial.println("ATRAS");
        break;
      case 4: // est4
        estado = 0;
        GIRO_DER;
        Serial.println("GIRO_DER");
        break;
      case 5: // est5
        estado = 6;
        ATRAS;
        Serial.println("ATRAS");
        break;
      case 6: // est6
        estado = 7;
        GIRO_IZQ;
        Serial.println("GIRO_IZQ");
        break;
      case 7: // est7
        estado = 8;
        GIRO_IZQ;
        Serial.println("GIRO_IZQ");
        break;
      case 8: // est8
        estado = 9;
        ADELANTE;
        Serial.println("ADELANTE");
        break;
      case 9: // est9
        estado = 10;
        ADELANTE;
        Serial.println("ADELANTE");
        break;
      case 10: // est10
        estado = 11;
        GIRO_DER;
        Serial.println("GIRO_DER");
        break;
      case 11: // est11
        estado = 0;
        GIRO_DER;
        Serial.println("GIRO_DER");
        break;
    } // end case

  } // end while
} // end Main (loop)
