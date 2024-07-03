

//////// UNA PELL DISTANT - EUFÒNIC 2024

/* Este código envía un mensaje por Serial cada vez que cae una gotita a tres sensores de agua Fonduino
  Tutorial Fonduino:  https://arduinogetstarted.com/tutorials/arduino-water-sensor
  Manda un "0" cundo el sensor A detecta una gota
  Manda un "1" cuando el sensor B detecta una gota
  Manda un "2" cuando el sensor C detecta una gota
  Se usan tres potenciómetros para regular los umbrales de sensibilidad de cada sensores.
  Se activa una máquina de estados que enciende y apaga tres relés (conectados a tres lásers) y tres leds indicadores.
  Los mensajes por serial son luego recibidos por un script en Python.
  2-jul-24
*/

/*
Poten: A3,A4,A5
sensores: A0,A1,A2
sensores: 2,3,4
leds: 10,11,12

*/

//BOTON y LED 13
const int ledPin_A = 10;
const int ledPin_B = 11;
const int ledPin_C = 12;

//SENSOR AGUA A
#define POWER_PIN_A 2
#define SIGNAL_PIN_A A2
int value_A = 0;
int umbral_A;
const int pinpoten_A = A3;
int val_pA;  //Poten

//SENSOR AGUA B
#define POWER_PIN_B 3
#define SIGNAL_PIN_B A1
int value_B = 0;
int umbral_B;
const int pinpoten_B = A4;
int val_pB;  //Poten

//SENSOR AGUA C
#define POWER_PIN_C 4
#define SIGNAL_PIN_C A0
int value_C = 0;
int umbral_C;
const int pinpoten_C = A5;
int val_pC;  //Poten

//RELAYS
const int RELAY_PIN_A = 7;
const int RELAY_PIN_B = 8;
const int RELAY_PIN_C = 9;


//Maquina de Estados
int edoSensor_A = 0;
int edoPrevioSen_A = 0;
int edoRelay_A = 0;
int valbol_A;

int edoSensor_B = 0;
int edoPrevioSen_B = 0;
int edoRelay_B = 0;
int valbol_B;

int edoSensor_C = 0;
int edoPrevioSen_C = 0;
int edoRelay_C = 0;
int valbol_C;




void setup() {
  Serial.begin(9600);

  pinMode(POWER_PIN_A, OUTPUT);
  digitalWrite(POWER_PIN_A, LOW);
  pinMode(POWER_PIN_B, OUTPUT);
  digitalWrite(POWER_PIN_B, LOW);
  pinMode(POWER_PIN_C, OUTPUT);
  digitalWrite(POWER_PIN_C, LOW);

  pinMode(ledPin_A, OUTPUT);
  pinMode(ledPin_B, OUTPUT);
  pinMode(ledPin_C, OUTPUT);
  //

  pinMode(pinpoten_A, INPUT);  //poten A
  pinMode(pinpoten_B, INPUT);  //poten B
  pinMode(pinpoten_C, INPUT);  //poten C

  //Relays
  pinMode(RELAY_PIN_A, OUTPUT);
  pinMode(RELAY_PIN_B, OUTPUT);
  pinMode(RELAY_PIN_C, OUTPUT);

  digitalWrite(RELAY_PIN_A, HIGH); // OFF
  digitalWrite(RELAY_PIN_B, HIGH); // OFF
  digitalWrite(RELAY_PIN_C, HIGH); // OFF
}

void loop() {
  potenUmbral_A();
  potenUmbral_B();
  potenUmbral_C();
  sensor_Agua_Gota_A();
  sensor_Agua_Gota_B();
  sensor_Agua_Gota_C();
  relay_A();
  relay_B();
  relay_C();


  if (value_A >= umbral_A) {
    //   Serial.println(0);
    digitalWrite(ledPin_A, HIGH);
    valbol_A = 1;
  } else {
    digitalWrite(ledPin_A, LOW);
    valbol_A = 0;
  }
  delay(100);

  if (value_B >= umbral_B) {
   // Serial.println(1);
    digitalWrite(ledPin_B, HIGH);
    valbol_B = 1;

  } else {
    digitalWrite(ledPin_B, LOW);
    valbol_B = 0;
  }
  delay(100);

  if (value_C >= umbral_C) {
   // Serial.println(2);
    digitalWrite(ledPin_C, HIGH);
    valbol_C = 1;

  } else {
    digitalWrite(ledPin_C, LOW);
    valbol_C = 0;
  }
  delay(100);

}






void sensor_Agua_Gota_A() {
  //lectura del sensor A
  digitalWrite(POWER_PIN_A, HIGH);
  delay(10);
  value_A = analogRead(SIGNAL_PIN_A);
  digitalWrite(POWER_PIN_A, LOW);
}


void sensor_Agua_Gota_B() {
  //lectura del sensor B
  digitalWrite(POWER_PIN_B, HIGH);
  delay(10);
  value_B = analogRead(SIGNAL_PIN_B);
  digitalWrite(POWER_PIN_B, LOW);
}

void sensor_Agua_Gota_C() {
  //lectura del sensor C
  digitalWrite(POWER_PIN_C, HIGH);
  delay(10);
  value_C = analogRead(SIGNAL_PIN_C);
  digitalWrite(POWER_PIN_C, LOW);
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

void potenUmbral_C() {
  val_pC = analogRead(pinpoten_C);
  umbral_C = map(val_pC, 0, 1023, 0, 500);
  umbral_C = constrain(umbral_C, 0, 500);
  //Serial.println("Umbral_C");
  //Serial.println(umbral_C);
}

void relay_A() {
  edoSensor_A = valbol_A;

  if (edoSensor_A == 1) {
    if (edoPrevioSen_A == 0) {
      if (edoRelay_A == 0) {
        // Serial.println("Relay_A On!");
        Serial.println(0);
        digitalWrite(RELAY_PIN_A, LOW);
        edoRelay_A = 1;
      } else if (edoRelay_A == 0) {
        //Serial.println("Relay_A Off!");
        digitalWrite(RELAY_PIN_A, HIGH);
        edoRelay_A = 0;
      }
    }
  }
  edoPrevioSen_A = edoSensor_A;
  delay(100);
}


void relay_B() {
  edoSensor_B = valbol_B;

  if (edoSensor_B == 1) {
    if (edoPrevioSen_B == 0) {
      if (edoRelay_B == 0) {
        //Serial.println("Relay_B On!");
        Serial.println(1);
        digitalWrite(RELAY_PIN_B, LOW);
        edoRelay_B = 1;
      } else if (edoRelay_B == 1) {
        // Serial.println("Relay_B Off!");
        digitalWrite(RELAY_PIN_B, HIGH);
        edoRelay_B = 0;
      }
    }
  }
  edoPrevioSen_B = edoSensor_B;
  delay(100);
}

void relay_C() {
  edoSensor_C = valbol_C;

  if (edoSensor_C == 1) {
    if (edoPrevioSen_C == 0) {
      if (edoRelay_C == 0) {
        //Serial.println("Relay_C On!");
        digitalWrite(RELAY_PIN_C, LOW);
        Serial.println(2);
        edoRelay_C = 1;
      } else if (edoRelay_C == 1) {
        // Serial.println("Relay_C Off!");
        digitalWrite(RELAY_PIN_C, HIGH);
        edoRelay_C = 0;
      }
    }
  }
  edoPrevioSen_C = edoSensor_C;
  delay(100);
}
