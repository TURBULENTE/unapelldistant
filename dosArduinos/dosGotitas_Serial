/* Este código envía dos mensajes por Serial, cada vez que cae una gotita en el sensor de agua Fonduino
    Basado en el ejemplo de:  https://arduinogetstarted.com/tutorials/arduino-water-sensor
*/

// Update 20/05/23
//Mandaremos un número distinto por cada sensor


//Sensor A
#define POWER_PIN_A  7
#define SIGNAL_PIN_A A5

//Sensor 2
#define POWER_PIN_B  4
#define SIGNAL_PIN_B A4


//Valores y umbrales
int value_A = 0;
int value_B = 0;
int umbral_A = 200;
int umbral_B = 200;



void setup() {
  Serial.begin(9600);
  
  pinMode(POWER_PIN_A, OUTPUT);
  digitalWrite(POWER_PIN_A, LOW);

  pinMode(POWER_PIN_B, OUTPUT);
  digitalWrite(POWER_PIN_B, LOW);
}

void loop() {

  //Lectura Sensor A
  digitalWrite(POWER_PIN_A, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value_A = analogRead(SIGNAL_PIN_A); // read the analog value from sensor
  digitalWrite(POWER_PIN_A, LOW);   // turn the sensor OFF

  //Lectura Sensor B
  digitalWrite(POWER_PIN_B, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value_B = analogRead(SIGNAL_PIN_B); // read the analog value from sensor
  digitalWrite(POWER_PIN_B, LOW);   // turn the sensor OFF


  ////////////////////// Evaluación de valores y envío por Serial
  
  if (value_A >= umbral_A) {
    Serial.println(1);
  } else {
    Serial.println(0);
  }

  if (value_B >= umbral_B) {
    Serial.println(2);
  } else {
    Serial.println(0);
  }

  delay(100); // Tiempo de espera / muestreo 
}
