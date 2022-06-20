/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLgXI02Poc"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "hkk60hlsp_zOxMeYsbg_Hm4ndoTXIpTu"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define soil A0
#define waterPump 13
float soilLevel, soilR;

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "MayuHotspot";
char pass[] = "hemu6514";

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  if (param.asInt()==1){
    digitalWrite(2,LOW);
  }
  else{
    digitalWrite(2,HIGH);
  }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  pinMode(waterPump,OUTPUT);
  Blynk.begin(auth, ssid, pass);
}
void sendSensor()
{
  readSoil();
  
 if(soilLevel<50)
  {    
    digitalWrite(waterPump, LOW);
    Blynk.virtualWrite(V1, 1);
  }
  else
  {
        digitalWrite(waterPump, HIGH);
        Blynk.virtualWrite(V1, 0);
  }
}
void readSoil()
{
  soilR=analogRead(soil);
  Serial.print("soilR: ");  
  Serial.println(soilR);
  soilLevel=map(soilR, 0, 1024, 100,0); // adjust soil level here
  Serial.print("soilLevel: "); 
  Serial.println(soilLevel);
  Blynk.virtualWrite(V2, soilLevel);
  delay(1000);
}

void loop()
{
  Blynk.run();

 // Update state
  sendSensor();
  delay(1000);
}
