/*************************************************************

  Smart Farming DEMO
  By N Academy
  October 16, 2022
  
 *************************************************************/

#define BLYNK_TEMPLATE_ID "TMPLDgoriXJR"
#define BLYNK_DEVICE_NAME "Kidbright"
#define BLYNK_AUTH_TOKEN "gm9YE_HT3Ey6MOX6zikYLrbTKHV2S3a3"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "@LINPHA-WIFI_2.4GHz";
char pass[] = "";

bool autoCtrl = false;

BlynkTimer timer;

// From manual/auto switch
//////////////////////////////////////////////////////////
BLYNK_WRITE(V0){
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("Mode: ");
  if(pinValue == 1)
  {
    Serial.println("Auto");
    autoCtrl = true;
  }
  else
  {
    Serial.println("Manual");
    autoCtrl = false;
  }
}

// To solenoid valve
//////////////////////////////////////////////////////////
BLYNK_WRITE(V2){
  int pinValue = param.asInt();
  if(pinValue == 1){
    digitalWrite(19, HIGH);
  }
  else{
    digitalWrite(19, LOW);
  }
}

// Timer trig every 100mS
//////////////////////////////////////////////////////////
void myTimerEvent(){
  bool val = digitalRead(18);
  Serial.println(val);
  Blynk.virtualWrite(V1, val);

  if(autoCtrl){
      Blynk.virtualWrite(V2, val);
      digitalWrite(19, val);
  }
}

void setup(){
  Serial.begin(115200);

  pinMode(18, INPUT);
  pinMode(19, OUTPUT);
  
  timer.setInterval(100L, myTimerEvent); //Staring a timer

  Blynk.begin(auth, ssid, pass);
}

void loop(){
  Blynk.run();
  timer.run(); 
}
