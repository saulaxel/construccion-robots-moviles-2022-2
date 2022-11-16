/************************************************************************
 * Algoritmo de Evasión de Obstaculos                                   *
 * Programa en C de Arduino para un robot móvil que evade               *
 * obstáculos.                                                          *
 * Lab. Bio-Robótica                                                    *
 * FI-UNAM                                                              *
 *                                                                      *
 ************************************************************************/

// Macros
#define TAM_ARRAY(arr) (sizeof(arr) / sizeof(*(arr)))

// Definicion de constantes
#define ADELANTE move_robot(AVANCE, 0.0f)
#define ATRAS move_robot(-AVANCE, 0.0)
#define GIRO_IZQ move_robot(0.0, GIRO)
#define GIRO_DER move_robot(0.0, -GIRO)
#define ALTO move_robot(0.0,0.0)

enum motors {
  up,
  right,
  down,
  left,
  num_motors // Cantidad de motores
};
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

// La cantidad que hay de cada tipo de sensor
const size_t num_ldrs = TAM_ARRAY(pin::ldr);
const size_t num_infras = TAM_ARRAY(pin::infra);
const size_t num_ultras = TAM_ARRAY(pin::ultra_trig);

// Auxiliares para el ultrasónico
const float centimetros_por_microsegundo = (1.0f / 29.2f);
const long umbral_ultra = 15;

// Auxiliares para el motor
enum Direction {
  clockwise,
  anticlockwise,
};
int motor_speed = 50;

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

void setMotorDirection(int index, Direction d) {
  if (d == clockwise) {
    digitalWrite(pin::motor_direction[index], HIGH);
    //digitalWrite(pin::motor_direction[index], LOW);
  } else {
    //digitalWrite(dirPin1, LOW);
    //digitalWrite(dirPin2, HIGH);
  }
}

void setMotorSpeed(int motor, int motorSpeed) {
  //analogWrite(speedPin, motorSpeed);
}

void avance_robot(float distancia)
{
  
}

void giro_robot(float angulo)
{
  
}

// Esta función hace que el robot primero gire un angulo y después avance una distancia
void move_robot(float distancia, float angulo)
{
  giro_robot(angulo);
  avance_robot(distancia);
  delay(1000);
}
// Esta función lee el valor de un sensor, indicando su tipo y numero, y regresa su valor
float shs(String sensor, int num_sensor)
{
  float x=1.0;

  if (sensor == "ultra") {
    long tiempo_ir_regresar_us, tiempo_ida_us;
    long distancia_cm;
    
    // Indicar al sensor ultrasónico que envíe una onda de sonido
    digitalWrite(pin::ultra_trig[num_sensor], LOW);
    delayMicroseconds(4);
    digitalWrite(pin::ultra_trig[num_sensor], HIGH);
    delayMicroseconds(10);
    digitalWrite(pin::ultra_trig[num_sensor], LOW);  

    // Leemos de Echo el tiempo que tarda la onda en regresar
    tiempo_ir_regresar_us = pulseIn(pin::ultra_echo[num_sensor], HIGH);
    tiempo_ida_us = tiempo_ir_regresar_us / 2;

    distancia_cm = tiempo_ida_us * centimetros_por_microsegundo;

    if (distancia_cm < umbral_ultra) {
      x = 0;
    }
  }
  
  return(x);
}
// Algoritmo de evasión de obstáculos
void loop(){
  int estado = 0;
  float Si, Sm, Sd;
  float AVANCE=.1;
  float GIRO= 0.7854;
  // Estado inicial
  estado = 0;
  // Loop infinito
  while(1){
    // Se leen los sensores
    Si = shs("ultra", 0);
    Sm = shs("ultra", 1);
    Sd = shs("contact", 2);
    
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
