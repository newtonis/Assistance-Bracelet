#include <TimeLib.h>
#include <TimeAlarms.h>
#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include <String.h>
#include <EEPROM.h>

//Set Alarms Libraries
#include <NTPClient.h>
#include <WiFiUdp.h>

const long utcOffsetInSeconds = -10800;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


//Wifi 
const char *ssid = "IPLANLiv-VALENTINA-2.4Ghz";        // Your WiFi SSID
const char *password = "valen1997";    // Your WiFi Password


//Firebase
const char *FIREBASE_HOST = "proyectofinalapp-28cef-default-rtdb.firebaseio.com";
const char *FIREBASE_AUTH = "SCi3dGHJOAJpNqHCZnlCmhzPCm1x2ZEuA1GlohjB";
FirebaseData firebaseData;


AlarmId id;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

bool iterar = true;
String path = "/Pulseras/Valen";
String stringData;



#define LED1 D1
#define LED2 D2

void MorningAlarm() {
  digitalWrite(LED1,HIGH);
  //while(1){
  Serial.println("Alarm: - turn lights off");  
  //}
  
}


void setup() {
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

  //Connect to WiFi
  WiFi.enableInsecureWEP(true);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Set your Firebase info
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //Enable auto reconnect the WiFi when connection lost
  Firebase.reconnectWiFi(true);

  timeClient.begin();
  timeClient.update();

  setTime(timeClient.getHours(),timeClient.getMinutes(),timeClient.getSeconds(),22,10,21); //HACER QUE NO QUEDE HARDCODEADO
  Alarm.alarmRepeat(dowFriday,2,49,0, MorningAlarm);
}

void loop() 
{
    
    digitalClockDisplay();  
    Alarm.delay(1000);
      /*timeClient.update();
      Serial.print(daysOfTheWeek[timeClient.getDay()]);
      Serial.print(", ");
      Serial.print(timeClient.getHours());
      Serial.print(":");
      Serial.print(timeClient.getMinutes());
      Serial.print(":");
      Serial.println(timeClient.getSeconds());*/
  // put your main code here, to run repeatedly:
  while(iterar)
  {
    //     Firebase.setInt(firebaseData, "lectura1", 512);
    //     Firebase.setString(firebaseData, "string1", "On");
    //     Firebase.getInt(firebaseData, "lectura1");
    //     Serial.println(firebaseData.intData());
    //     delay(250);

  
    Firebase.getString(firebaseData, path + "/Medicamentos");
    stringData = firebaseData.stringData();
    stringData = stringData.substring(6, stringData.length()-1);
    Serial.println(stringData);
    
    stringData.replace(':',' ');
    stringData.replace('"',' ');
    stringData.replace(" ","");
    stringData.replace(',',' ');
    stringData.replace(" ","");
    Serial.println(stringData);

    //for (int i = 1; i < sizeof(stringData); i++) 
    //{
        //GUARDAR DATOS EN EEPROM 
    //}
  
    //LEER DATOS EN EEPROM 

    
    //GENERAR ALARMAS
    //Alarm.alarmRepeat(dowFriday,2,20,0, MorningAlarm);
    
    iterar=false;
  }

//    digitalWrite(LED1,HIGH);
//    delay(500);
//    digitalWrite(LED1,LOW);
//    digitalWrite(LED2,HIGH);
//    delay(1700);
//    digitalWrite(LED2,LOW);
//    delay(100);
}





//int EEPROMAnythingWrite(int pos, char *zeichen, int lenge)
//{
//  for (int i = 0; i < lenge; i++)
//  {
//    EEPROM.write(pos + i, *zeichen);
//    zeichen++;
//  }
//  return pos + lenge;
//}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
