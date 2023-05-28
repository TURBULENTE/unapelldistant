/* Este código envía un mensaje por Serial cada vez que cae una gotita a dos sensores de agua Fonduino
    Basado en el ejemplo de:  https://arduinogetstarted.com/tutorials/arduino-water-sensor
  Manda un "0" cundo el sensor A detecta una gota
  Manda un "1" cuando el sensor B detecta una gota
  Manda un "3" cuando un botón está presionado
  Se usan dos potenciómetros para regular los umbrales de sensibilidad de los sensores.
*/

// Update 26/05/23
//Mandaremos un número distinto por cada sensor

//BOTON y LED 13
const int ledPin_A = 11;
const int ledPin_B = 12;
const int inputPin = 9; //boton
int val_Bot; // boton




//SENSOR AGUA A (Arriba)
#define POWER_PIN_A  3
#define SIGNAL_PIN_A A0
int value_A = 0;
int umbral_A;
const int pinpoten_A = A4;
int val_pA; //Poten

//SENSOR AGUA B (Abajo)
#define POWER_PIN_B  2
#define SIGNAL_PIN_B A1
int value_B = 0;
int umbral_B;
const int pinpoten_B = A3;
int val_pB; //Poten



void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT); //boton

  pinMode(POWER_PIN_A, OUTPUT);
  digitalWrite(POWER_PIN_A, LOW);

  // Comentar para usar solo un sensor
  pinMode(POWER_PIN_B, OUTPUT);
  digitalWrite(POWER_PIN_B, LOW);
  pinMode(ledPin_A, OUTPUT);
  pinMode(ledPin_B, OUTPUT);
  //

  pinMode(pinpoten_A, INPUT);//poten A
  pinMode(pinpoten_B, INPUT);//poten B
}

void loop() {


 // potenUmbral_A();
  potenUmbral_B(); // Comentar para usar solo 1 sensor de agua
  //sensor_Agua_Gota_A();
  sensor_Agua_Gota_B(); // Comentar para usar solo 1 sensor de agua
  boton();

}






void sensor_Agua_Gota_A() {

  //lectura del sensor A
  digitalWrite(POWER_PIN_A, HIGH);
  delay(10);
  value_A = analogRead(SIGNAL_PIN_A);
  digitalWrite(POWER_PIN_A, LOW);


  if (value_A >= umbral_A) {
    Serial.println(1);
    digitalWrite(ledPin_A, HIGH);
  } else {
    //Serial.println(0);
    digitalWrite(ledPin_A, LOW);
  }

  delay(100);

}


void sensor_Agua_Gota_B() {

  //lectura del sensor B
  digitalWrite(POWER_PIN_B, HIGH);
  delay(10);
  value_B = analogRead(SIGNAL_PIN_B);
  digitalWrite(POWER_PIN_B, LOW);

  if (value_B >= umbral_B) {
    Serial.println(2);
    digitalWrite(ledPin_B, HIGH);
  } else {
    // Serial.println(0);
    digitalWrite(ledPin_B, LOW);
  }

  delay(100);

}

void boton() {
  val_Bot = digitalRead(inputPin);
  if (val_Bot == HIGH)
  {
    Serial.println(3);
    digitalWrite(ledPin_A, HIGH);
    digitalWrite(ledPin_B, HIGH);
  }
  else
  {
    digitalWrite(ledPin_A, LOW);
    digitalWrite(ledPin_B, LOW);
  }
}


void potenUmbral_A() {
  val_pA = analogRead(pinpoten_A);
  umbral_A = map(val_pA, 0, 1023, 0, 500);
  umbral_A = constrain(umbral_A, 0, 500);
  //Serial.println("Umbral_A");
  //Serial.println(umbral_A);

}

void potenUmbral_B() {
  val_pB = analogRead(pinpoten_B);
  umbral_B = map(val_pB, 0, 1023, 0, 500);
  umbral_B = constrain(umbral_B, 0, 500);
  //Serial.println("Umbral_B");
  //Serial.println(umbral_B);

}
