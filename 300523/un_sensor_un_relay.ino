/* Este código envía un mensaje por Serial cada vez que cae una gotita a dos sensores de agua Fonduino
    Basado en el ejemplo de:  https://arduinogetstarted.com/tutorials/arduino-water-sensor
  Manda un "0" cundo el sensor A detecta una gota
  Manda un "1" cuando el sensor B detecta una gota
  Manda un "3" cuando un botón está presionado
  Se usa un potenciómetro para regular los umbrales de sensibilidad de los sensores.
  Sensor Intermedio
*/


//BOTON y LED 13
const int ledPin_A = 12;
const int inputPin = 9; //boton
int val_Bot; // boton



//SENSOR AGUA A (Arriba)
#define POWER_PIN_A  3
#define SIGNAL_PIN_A A0
int value_A = 0;
int umbral_A;
const int pinpoten_A = A4;
int val_pA; //Poten



//RELAY
const int RELAY_PIN_A = 8;
//Maquina de Estados
int edoSensor_A = 0;
int edoPrevioSen_A = 0;
int edoRelay_A = 0;
int valbol_A;



void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT); //boton

  pinMode(POWER_PIN_A, OUTPUT);
  digitalWrite(POWER_PIN_A, LOW);

  pinMode(ledPin_A, OUTPUT);
  pinMode(pinpoten_A, INPUT);//poten A
  pinMode(RELAY_PIN_A, OUTPUT); //Relay
}

void loop() {

  boton();
  potenUmbral_A();
  sensor_Agua_Gota_A();
  relay_A();

}


void sensor_Agua_Gota_A() {

  //lectura del sensor A
  digitalWrite(POWER_PIN_A, HIGH);
  delay(10);
  value_A = analogRead(SIGNAL_PIN_A);
  digitalWrite(POWER_PIN_A, LOW);

  //Verificación de paso de umbral
  if (value_A >= umbral_A) {
    Serial.println(1);
    digitalWrite(ledPin_A, HIGH);
    valbol_A = 1;
  } else {
    digitalWrite(ledPin_A, LOW);
    valbol_A = 0;
  }
  delay(100);

}




void boton() {
  val_Bot = digitalRead(inputPin);
  if (val_Bot == HIGH)
  {
    Serial.println(3);
    digitalWrite(ledPin_A, HIGH);
  }
  else
  {
    digitalWrite(ledPin_A, LOW);
  }
}


void potenUmbral_A() {
  val_pA = analogRead(pinpoten_A);
  umbral_A = map(val_pA, 0, 1023, 0, 500);
  umbral_A = constrain(umbral_A, 0, 500);
  //Serial.println("Umbral_A");
  //Serial.println(umbral_A);
  //Serial.println(val_pA);

}



void relay_A () {
  edoSensor_A = valbol_A;

  if (edoSensor_A == 1) {
    if (edoPrevioSen_A == 0) {
      if (edoRelay_A == 0) {
        // Serial.println("Relay_A On!");
        digitalWrite(RELAY_PIN_A, LOW);
        edoRelay_A = 1;
      } else if (edoRelay_A == 1) {
        //Serial.println("Relay_A Off!");
        digitalWrite(RELAY_PIN_A, HIGH);
        edoRelay_A = 0;
      }
    }
  }
  edoPrevioSen_A = edoSensor_A;
  delay(100);

}
