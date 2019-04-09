/****************************************
 * Include Libraries
 * iwan cilibur
 * www.interactiverobotics.club
 ****************************************/

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "smarthomesed.firebaseio.com"
#define FIREBASE_AUTH "7A4JNrtAgxdDCoyZ5CYwlVx9xPvMsEZLH1lNGzaf"
#define WIFISSID "www.interactiverobotics.club2" // Assign your WiFi SSID
#define PASSWORD  "cilibur2019" // Assign your WiFi password

const int relay1 = D5;
const int relay2 = D6;
const int relay3 = D7;
const int relay4 = D8;
const int sensor = A0;
/****************************************
 * Main Functions
 ****************************************/
void setup() {
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(sensor, INPUT);

  WiFi.begin(WIFISSID, PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.set("relay1", 0);
  Firebase.set("relay2", 0);
  Firebase.set("relay3", 0);
  Firebase.set("relay4", 0);

  Firebase.set("datasensor", 0);
  
}

void loop() {
  digitalWrite(relay1, Firebase.getInt("relay1"));
  digitalWrite(relay2, Firebase.getInt("relay2"));
  digitalWrite(relay3, Firebase.getInt("relay3"));
  digitalWrite(relay4, Firebase.getInt("relay4"));

  int datacahaya=analogRead(sensor);
  Serial.print("Cahaya diterima : ");
  Serial.println(datacahaya);
  Firebase.setFloat("sunlight", datacahaya);
  delay(500);
}
