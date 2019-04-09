  #include <ESP8266WiFi.h>
  #include<FirebaseArduino.h>
  #define FIREBASE_HOST "smarthomesed.firebaseio.com"
  #define FIREBASE_AUTH "7A4JNrtAgxdDCoyZ5CYwlVx9xPvMsEZLH1lNGzaf"
  #define WIFISSID "www.interactiverobotics.club" // Assign your WiFi SSID
  #define PASSWORD  "cilibur2019" // Assign your WiFi password
  int Ledpin=D7;
  void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200); //baud rate ,if you want to see the process in the serial monitor ,same baud rate should be set.
    pinMode(Ledpin,OUTPUT);
    WiFi.begin(WIFISSID,PASSWORD);
    Serial.print("connecting");
    while (WiFi.status()!=WL_CONNECTED){
      Serial.print(".");
      delay(500);
    }
    Serial.println();
    Serial.print("connected:");
    Serial.println(WiFi.localIP());
  
    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
    Firebase.set("FB1",0);//the variable in which is used in our Firebase and MIT App Inventor
    Firebase.set("FB2",0);//the variable in which is used in our Firebase and MIT App Inventor
  }
  void firebasereconnect()
  {
    Serial.println("Trying to reconnect");
      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    }
  int l;
  void loop() {
    if (Firebase.failed()) {
        Serial.print("setting number failed:");
        Serial.println(Firebase.error());
        firebasereconnect();
        return;
    }
    l=Firebase.getString("FB1").toInt();//The value read from the firebase is read in the form of String and is converted into Integer
    if(l==1){
        digitalWrite(Ledpin,HIGH);
        Serial.println("lightON");
      }
      else if(l==0){
        digitalWrite(Ledpin,LOW);
        Serial.println("lightOFF");
      }
  }
