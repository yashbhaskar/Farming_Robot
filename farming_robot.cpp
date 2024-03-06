#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "All in one Agriculture Robot"
#define BLYNK_AUTH_TOKEN ""  //copy and paste Blynk application auth token

#define EXPECTED_V_OUT 12.5    // The intented voltage, 12 V

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <Servo.h>    

const int BatteryPin = A0;
 
//Motor PINs
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5
   
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
#define SPEED 255 
int adc_read = 0;
float battery_voltage = 0;
BlynkTimer timer;
int percent = 0;
Servo servo;

char auth[] = ""; //Enter your Blynk application auth token
char ssid[] = "FarmingRobot"; //Enter your WIFI name
char pass[] = "1234567890"; //Enter your WIFI passowrd

const int relay1 =15;// pin of D8
 
void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(15, OUTPUT);
 // pinMode(12, OUTPUT);
  digitalWrite(15,HIGH);  // Set digital pin 2 LOW
  servo.attach(12);
 Serial.begin(9600);
 Blynk.begin(auth,ssid,pass,"blynk.cloud",80);                     //12
}
 
BLYNK_WRITE(V0) {
  forward = param.asInt();
}
 
BLYNK_WRITE(V1) {
  backward = param.asInt();
}
 
BLYNK_WRITE(V2) {
  right = param.asInt();
}
 
BLYNK_WRITE(V3) {
  left = param.asInt();
}
 

BLYNK_WRITE(V4) {
  Speed = param.asInt();
}


BLYNK_WRITE(V6) // Executes when the value of virtual pin 0 changes
 {
  if(param.asInt() == 1)
     {
    // execute this code if the switch widget is now ON
    digitalWrite(15,LOW);  // Set digital pin 2 HIGH
    }
 else
    {
    // execute this code if the switch widget is now OFF
    digitalWrite(15,HIGH);  // Set digital pin 2 LOW
    }
}




void smartcar() {
  if (forward == 1) {
    carforward();
    Serial.println("carforward");
  } else if (backward == 1) {
    carbackward();
    Serial.println("carbackward");
  } else if (left == 1) {
    carturnleft();
    Serial.println("carfleft");
  } else if (right == 1) {
    carturnright();
    Serial.println("carright");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    carStop();
    Serial.println("carstop");
  }
}
void loop() {

   adc_read = analogRead(BatteryPin);

  battery_voltage = (adc_read*(4.3/1023)*(6))/2;

  percent = battery_voltage * 100 / EXPECTED_V_OUT;
 
  Blynk.run();
  timer.run();
  delay(1000);
  smartcar();
}

void carforward() {
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carbackward() {
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carturnleft() {
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carturnright() {
  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}