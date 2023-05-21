/* Este código envía un mensaje por Serial cada vez que cae una gotita en el sensor de agua Fonduino
    Basado en el ejemplo de:  https://arduinogetstarted.com/tutorials/arduino-water-sensor
  Manda un "3" por serial cuando un botón está presionado
  usa un potenciómetro para regular el umbral del sensor de agua
*/

// Update 20/05/23
//Mandaremos un número distinto por cada sensor

//BOTON, POTEN y LED 13
const int ledPin = 13;
const int inputPin = 9;
const int potPin = 0;
int val; // boton
int valP; //Poten

//SENSOR AGUA
#define POWER_PIN  7
#define SIGNAL_PIN A5
int value = 0;
int umbral0;

void setup() {
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, LOW);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  potenUmbral();
  sensorAgua_UnaGota();
  boton();

}






void sensorAgua_UnaGota() {

  digitalWrite(POWER_PIN, HIGH);
  delay(10);
  value = analogRead(SIGNAL_PIN);
  digitalWrite(POWER_PIN, LOW);

  //Serial.println(value);
  if (value >= umbral0) {
    Serial.println(1);
    digitalWrite(ledPin, HIGH);
  } else {
    Serial.println(0);
    digitalWrite(ledPin, LOW);
  }

  delay(100);

}

void boton() {
  val = digitalRead(inputPin);
  if (val == HIGH)
  {
    Serial.println(3);
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
}


void potenUmbral() {
  valP = analogRead(potPin);
  umbral0 = map(valP, 0, 1023, 0, 500);
  //Serial.println(umbral0);

}
