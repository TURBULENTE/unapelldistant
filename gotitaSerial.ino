/* Este código envía un "0" por serial, cada vez que cae una gotita en el sensor de agua Fonduino
 *  Basado en el ejemplo de:  https://arduinogetstarted.com/tutorials/arduino-water-sensor
 */

// Update 20/05/23
//Mandaremos un número distinto por cada sensor

// Sensor 1
#define POWER_PIN  7
#define SIGNAL_PIN A5

int value = 0; // variable to store the sensor value
int umbral0= 150;

void setup() {
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
}

void loop() {
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF

  /*Serial.print("Sensor value: ");
  Serial.println(value);*/

  delay(100);

  if (value >= umbral0){
Serial.println(0);
  }
  }
