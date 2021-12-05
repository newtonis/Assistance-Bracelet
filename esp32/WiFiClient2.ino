/********TESIS - PULSERA DE ASISTENCIA PARA ADULTOS MAYORES******/

// ------------- INCLUDES -----------
#include <WiFi.h>
#include <FirebaseESP32.h>


//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#include <TimeLib.h>
#include <TimeAlarms.h>
//Set Alarms Libraries
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <String.h>


//------------- DEFINES -----------

// Insert Firebase project API Key
#define API_KEY "AIzaSyAUcwsuuk5Gk6r2sWBbq49TCwXLJfxmaNI"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://proyectofinalapp-28cef-default-rtdb.firebaseio.com" 


#define LED1_R  23 // GIOP23
#define LED1_G  22 // GIOP22
#define LED1_B  21 // GIOP21

#define LED2_R   19 // GIOP23
#define LED2_G  18 // GIOP22
#define LED2_B   5 // GIOP21

#define LED3_R    4 // GIOP23
#define LED3_G  2 // GIOP22
#define LED3_B   15 // GIOP21

#define VIBRATOR 32 //GPIO32
#define PIN_BUTTON_ALARM  33 //GPIO33
#define PIN_BUTTON_EMERGENCY 27 //GPIO27

//----------------PROTOTYPES--------------


String readPills(FirebaseData& fbdo, String path);
timeDayOfWeek_t readDay(char numero);
int readHour(char letra);
void turnOnColorAlarm(timeDayOfWeek_t dia,int hora,char color);
void configAlarms(String stringData);
void startWifi(const char* ssid,const char* password);
void startFirebase(void);
void startTime(void);void digitalClockDisplay(void);
void printDigits(int digits);

bool ledUsed [3] = {false,false,false};
void initPins(void);

void alarmYellow(void);
void alarmGreen(void);
void alarmOrange(void);
void alarmCyann(void);
void alarmBlue(void);
void alarmViolet(void);
void alarmPink(void);
void alarmRed(void);

void alarmBegin(void);
void alarmSnooze(void);
void alarmOff(void);
void ledsOff(void);

void led1Yellow(void);
void led1Green(void);
void led1Cyann(void);
void led1Blue(void);
void led1Violet(void);
void led1Pink(void);
void led1Red(void);
void led1Orange(void);
void led2Yellow(void);
void led2Green(void);
void led2Cyann(void);
void led2Blue(void);
void led2Violet(void);
void led2Pink(void);
void led2Red(void);
void led2Orange(void);
void led3Yellow(void);
void led3Green(void);
void led3Cyann(void);
void led3Blue(void);
void led3Violet(void);
void led3Pink(void);
void led3Red(void);
void led3Orange(void);


bool sendEmergencyToFirebase(String path);

//------------GLOBAL VARIABLES ----------

const long utcOffsetInSeconds = -10800;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

String path = "/Pulseras/uM2EWXjqzScC6VihyWm8btZP3Dt1/Malena";
String pillsData;
FirebaseData fbdo;
int emergencyOn = 1;
bool iterar = true;

AlarmId id;

FirebaseAuth auth;
FirebaseConfig config;


enum {LED1, LED2, LED3};

int counter;
bool alarmOn;
bool buttonPressed = false;
bool EmergencyPressed = false;

//------------------------------------------

String readPills(FirebaseData& fbdo, String path)
{
    String stringData;
    String temp_stringData;
    String pillsData;
    
    Firebase.getString(fbdo, path + "/Medicamentos");
    stringData = fbdo.stringData();
    stringData = stringData.substring(1, stringData.length()-1);
    int stringLength = stringData.length();
    pillsData = stringData.substring(24, 29);
    pillsData.replace(':',' ');
    pillsData.replace(" ","");
    for(int i=55 ; i < stringLength; i+=31)
    {
      temp_stringData = stringData.substring(i, i+5);
      temp_stringData.replace(':',' ');
      temp_stringData.replace(" ","");
      pillsData = pillsData + temp_stringData;
    }
    return pillsData;
}


timeDayOfWeek_t readDay(char numero) 
{
    timeDayOfWeek_t dia;
    switch (numero)
    {
      case '0':
        dia = dowSunday;
      break;
    
      case '1':
        dia = dowMonday;
      break;

      case '2':
        dia = dowTuesday;
      break;

      case '3':
        dia = dowWednesday;
      break;

      case '4':
        dia = dowThursday;
      break;
      
      case '5':
        dia = dowFriday;
      break;

      case '6':
        dia = dowSaturday;
      break;
        
      default:
        dia = dowInvalid;
      break;
    }

    return dia;
}


int readHour(char letra) 
{
    return letra - 'A';
}


void turnOnColorAlarm(timeDayOfWeek_t dia,int hora,char color)
{
      
   switch (color)
    {
      case 'a': 
        Alarm.alarmRepeat(dia,hora,15,0,alarmYellow);
        
      break;
    
      case 'b':
        Alarm.alarmRepeat(dia,hora,15,0,alarmGreen);
      break;

      case 'c':
        Alarm.alarmRepeat(dia,hora,0,0,alarmOrange);
      break;
    
      case 'd': 
        Alarm.alarmRepeat(dia,hora,0,0,alarmCyann);
        
      break;

      case 'e': 
        Alarm.alarmRepeat(dia,hora,15,0,alarmBlue);
        
      break;
    
      case 'f':
        Alarm.alarmRepeat(dia,hora,0,0,alarmViolet);
      break;

      case 'g':
        Alarm.alarmRepeat(dia,hora,0,0,alarmPink);
      break;
    
      case 'h':
        Alarm.alarmRepeat(dia,hora,0,0,alarmRed);
      break;
  
      default:
        color = DEFAULT;
      break;
    }
}

void configAlarms(String stringData)
{
    Serial.println(stringData);
    char letra_minuscula[100];
    char numero[100];
    char letra_mayuscula[100];

    timeDayOfWeek_t dia;
    int hora;
    char color;
    int i = 0;
    for (int j = 0; j < (stringData.length() / 3); j++) 
    {
        letra_minuscula[j] = stringData[i];
        numero[j] = stringData[i+1];
        letra_mayuscula[j] = stringData[i+2];

        dia = readDay(numero[j]);
        hora = readHour(letra_mayuscula[j]);
        color = letra_minuscula[j];
        Serial.println("--------------alarma----------------");
        Serial.println(dia);
        Serial.println(hora);
        Serial.println(color);
        Serial.println("------------------------------");

        turnOnColorAlarm(dia,hora,color);

        i+=3;
    }
}


void startWifi(const char* ssid,const char* password)
{
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

}


void startFirebase()
{
      bool signupOK = false;
    
    /* Assign the api key (required) */
    config.api_key = API_KEY;
  
    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;
  
    /* Sign up */
    if (Firebase.signUp(&config, &auth, "", "")) 
    {
      Serial.println("ok");
      signupOK = true;
    }
    
    else 
    {
      Serial.printf("error\n");
      Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }

      /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

void startTime()
{
  timeClient.begin();
  timeClient.update();
  
  String formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  String dayStamp = formattedDate.substring(0, splitT);
  int splitGuion1 = formattedDate.indexOf("-");
  int splitGuion2 = formattedDate.indexOf("-",splitGuion1+1);
  String ano = formattedDate.substring(2, splitGuion1);
  String mes = formattedDate.substring(splitGuion1+1, splitGuion2);
  String dia = formattedDate.substring(splitGuion2+1, dayStamp.length());
  
  timeClient.update();
  
  setTime(timeClient.getHours(),timeClient.getMinutes(),timeClient.getSeconds(),dia.toInt(),mes.toInt(),ano.toInt());
  
}

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

void initPins(void)
{
  pinMode(LED1_R, OUTPUT);
  pinMode(LED1_G, OUTPUT);
  pinMode(LED1_B, OUTPUT);
  
  pinMode(LED2_R, OUTPUT);
  pinMode(LED2_G, OUTPUT);
  pinMode(LED2_B, OUTPUT);
  
  pinMode(LED3_R, OUTPUT);
  pinMode(LED3_G, OUTPUT);
  pinMode(LED3_B, OUTPUT);

  pinMode(VIBRATOR, OUTPUT);
  pinMode(PIN_BUTTON_ALARM, INPUT);
  pinMode(PIN_BUTTON_EMERGENCY, INPUT);
}

void alarmBegin(void)
{
  alarmOn = true;

  led1Yellow(); //CAMBIAR
  led2Green(); //CAMBIAR
  led3Blue(); //CAMBIAR
  digitalWrite(VIBRATOR, 1);
  //digitalWrite(BUZZER , 1);
  counter = 0;
}

void alarmSnooze(void)
{
  digitalWrite(VIBRATOR, 0);
}

void alarmOff(void)
{
  ledsOff();
  //analogWrite(BUZZER, 0);
  alarmOn = false;
}


void alarmYellow(void)
{
  Serial.println("ALARMA-AMARILLA");
  if(ledUsed[0] == false)
  {
    led1Yellow();
    ledUsed[0] = true;
  }
  else if(ledUsed[1] == false)
  {
    led2Yellow();
    ledUsed[1] = true;
  }
  else if(ledUsed[2] == false)
  {
    led3Yellow();
    ledUsed[2] = true;
  }  
  digitalWrite(VIBRATOR, 1);
  //digitalWrite(BUZZER, 1);
  alarmOn = true;
  counter = 0;
}


void alarmGreen(void)
{
  Serial.println("ALARMA-VERDE");
  if(ledUsed[0] == false)
  {
    led1Green();
    ledUsed[0] = true;
  }
  else if(ledUsed[1] == false)
  {
    led2Green();
    ledUsed[1] = true;
  }
  else if(ledUsed[2] == false)
  {
    led3Green();
    ledUsed[2] = true;
  }  
  digitalWrite(VIBRATOR, 1);
  //digitalWrite(BUZZER, 1);
  alarmOn = true;
  counter = 0;
}

void alarmCyann(void)
{
  Serial.println("ALARMA-CYAN");
  if(ledUsed[0] == false)
  {
    led1Cyann();
    ledUsed[0] = true;
  }
  else if(ledUsed[1] == false)
  {
    led2Cyann();
    ledUsed[1] = true;
  }
  else if(ledUsed[2] == false)
  {
    led3Cyann();
    ledUsed[2] = true;
  }  
  digitalWrite(VIBRATOR, 1);
  //digitalWrite(BUZZER, 1);
  alarmOn = true;
  counter = 0;
}

void alarmBlue(void)
{
  Serial.println("ALARMA-AZUL");
  if(ledUsed[0] == false)
  {
    led1Blue();
    ledUsed[0] = true;
  }
  else if(ledUsed[1] == false)
  {
    led2Blue();
    ledUsed[1] = true;
  }
  else if(ledUsed[2] == false)
  {
    led3Blue();
    ledUsed[2] = true;
  }  
  digitalWrite(VIBRATOR, 1);
  //digitalWrite(BUZZER, 1);
  alarmOn = true;
  counter = 0;
}

void alarmViolet(void)
{
  Serial.println("ALARMA-VIOLETA");
  if(ledUsed[0] == false)
  {
    led1Violet();
    ledUsed[0] = true;
  }
  else if(ledUsed[1] == false)
  {
    led2Violet();
    ledUsed[1] = true;
  }
  else if(ledUsed[2] == false)
  {
    led3Violet();
    ledUsed[2] = true;
  }  
  digitalWrite(VIBRATOR, 1);
  //digitalWrite(BUZZER, 1);
  alarmOn = true;
  counter = 0;
}

void alarmPink(void)
{
  Serial.println("ALARMA-ROSA");
  if(ledUsed[0] == false)
  {
    led1Pink();
    ledUsed[0] = true;
  }
  else if(ledUsed[1] == false)
  {
    led2Pink();
    ledUsed[1] = true;
  }
  else if(ledUsed[2] == false)
  {
    led3Pink();
    ledUsed[2] = true;
  }  
  digitalWrite(VIBRATOR, 1);
  //digitalWrite(BUZZER, 1);
  alarmOn = true;
  counter = 0;
}

void alarmRed(void)
{
  Serial.println("ALARMA-ROJA");
  if(ledUsed[0] == false)
  {
    led1Red();
    ledUsed[0] = true;
  }
  else if(ledUsed[1] == false)
  {
    led2Red();
    ledUsed[1] = true;
  }
  else if(ledUsed[2] == false)
  {
    led3Red();
    ledUsed[2] = true;
  }  
  digitalWrite(VIBRATOR, 1);
  //digitalWrite(BUZZER, 1);
  alarmOn = true;
  counter = 0;
}


void alarmOrange(void)
{
  Serial.println("ALARMA-NARANJA");
  if(ledUsed[0] == false)
  {
    led1Orange();
    ledUsed[0] = true;
  }
  else if(ledUsed[1] == false)
  {
    led2Orange();
    ledUsed[1] = true;
  }
  else if(ledUsed[2] == false)
  {
    led3Orange();
    ledUsed[2] = true;
  }  
  digitalWrite(VIBRATOR, 1);
  //digitalWrite(BUZZER, 1);
  alarmOn = true;
  counter = 0;
}

//------------------------------------------------
void led1Cyann(void)
{
  analogWrite(LED1_R, 0);
  analogWrite(LED1_G, 100);
  analogWrite(LED1_B, 255);
}

void led1Blue(void)
{
  analogWrite(LED1_R, 0);
  analogWrite(LED1_G, 0);
  analogWrite(LED1_B, 255);
}

void led1Violet(void)
{
  analogWrite(LED1_R, 25);
  analogWrite(LED1_G, 0);
  analogWrite(LED1_B, 255);
}

void led1Pink(void)
{
  analogWrite(LED1_R, 255);
  analogWrite(LED1_G, 0);
  analogWrite(LED1_B, 255);
}

void led1Red(void)
{
  analogWrite(LED1_R, 255);
  analogWrite(LED1_G, 0);
  analogWrite(LED1_B, 0);
}

void led1Yellow(void)
{
  analogWrite(LED1_R, 255);
  analogWrite(LED1_G, 200);
  analogWrite(LED1_B, 0);
}

void led1Green(void)
{
  analogWrite(LED1_R, 0);
  analogWrite(LED1_G, 255);
  analogWrite(LED1_B, 0);
}

void led1Orange(void)
{
  analogWrite(LED1_R, 255);
  analogWrite(LED1_G, 25);
  analogWrite(LED1_B, 0);
}


// LED 2 - COLORS

void led2Yellow(void)
{
  analogWrite(LED2_R, 255);
  analogWrite(LED2_G, 200);
  analogWrite(LED2_B, 0);
}

void led2Green(void)
{
  analogWrite(LED2_R, 0);
  analogWrite(LED2_G, 255);
  analogWrite(LED2_B, 0);
}

void led2Cyann(void)
{
  analogWrite(LED2_R, 0);
  analogWrite(LED2_G, 100);
  analogWrite(LED2_B, 255);
}

void led2Blue(void)
{
  analogWrite(LED2_R, 0);
  analogWrite(LED2_G, 0);
  analogWrite(LED2_B, 255);
}

void led2Violet(void)
{
  analogWrite(LED2_R, 25);
  analogWrite(LED2_G, 0);
  analogWrite(LED2_B, 255);
}

void led2Pink(void)
{
  analogWrite(LED2_R, 255);
  analogWrite(LED2_G, 0);
  analogWrite(LED2_B, 255);
}

void led2Red(void)
{
  analogWrite(LED2_R, 255);
  analogWrite(LED2_G, 0);
  analogWrite(LED2_B, 0);
}

void led2Orange(void)
{
  analogWrite(LED2_R, 255);
  analogWrite(LED2_G, 25);
  analogWrite(LED2_B, 0);
}


// LED 3 - COLORS

void led3Yellow(void)
{
  analogWrite(LED3_R, 255);
  analogWrite(LED3_G, 200);
  analogWrite(LED3_B, 0);
}

void led3Green(void)
{
  analogWrite(LED3_R, 0);
  analogWrite(LED3_G, 255);
  analogWrite(LED3_B, 0);
}

void led3Cyann(void)
{
  analogWrite(LED3_R, 0);
  analogWrite(LED3_G, 100);
  analogWrite(LED3_B, 255);
}

void led3Blue(void)
{
  analogWrite(LED3_R, 0);
  analogWrite(LED3_G, 0);
  analogWrite(LED3_B, 255);
}

void led3Violet(void)
{
  analogWrite(LED3_R, 25);
  analogWrite(LED3_G, 0);
  analogWrite(LED3_B, 255);
}

void led3Pink(void)
{
  analogWrite(LED3_R, 255);
  analogWrite(LED3_G, 0);
  analogWrite(LED3_B, 255);
}

void led3Red(void)
{
  analogWrite(LED3_R, 255);
  analogWrite(LED3_G, 0);
  analogWrite(LED3_B, 0);
}

void led3Orange(void)
{
  analogWrite(LED3_R, 255);
  analogWrite(LED3_G, 25);
  analogWrite(LED3_B, 0);
}

//--------------------
void ledsOff(void) 
{
  analogWrite(LED1_R, 0);
  analogWrite(LED1_G, 0);
  analogWrite(LED1_B, 0);
  analogWrite(LED2_R, 0);
  analogWrite(LED2_G, 0);
  analogWrite(LED2_B, 0);
  analogWrite(LED3_R, 0);
  analogWrite(LED3_G, 0);
  analogWrite(LED3_B, 0);
  ledUsed [0] = false;
  ledUsed [1] = false;
  ledUsed [2] = false;
}


void setup()
{
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network 
    startWifi("IPLANLiv-VALENTINA-2.4Ghz","valen1997");
    //Then we connect to Firebase
    startFirebase();
    //start Time and TimeAlarm Libraries
    startTime();

    initPins();
    ledsOff();
    alarmOff();
    buttonPressed = false;
    //alarmBegin();
    counter = 0;
}

void loop()
{

  //digitalClockDisplay();  
  Alarm.delay(1000);
  while(iterar)
  {
    //read Pills from Firebase and config alarms 
    pillsData = readPills(fbdo, path);
    configAlarms(pillsData);
    iterar=false;
  }

  if(digitalRead(PIN_BUTTON_ALARM) == true)
  {
    //delay(500);
    if(buttonPressed == false)
    {
      //ledsOff();
      buttonPressed = true;
      if(alarmOn == true)
      {
        counter ++;
        if(counter == 1)
        {
          alarmSnooze();
        }
        else if(counter > 1)
        {
          alarmOff();
          counter = 0;
        }
      }
    }
  }
  else
  {
    buttonPressed = false;
  }

  if(digitalRead(PIN_BUTTON_EMERGENCY) == true)
  {
    Serial.println("Se presiono Emergencia");
    if(EmergencyPressed == false)
    {
      EmergencyPressed = true;
      sendEmergencyToFirebase(path);
      
    }
  }
  else
  {
    EmergencyPressed = false;
  }
  
}

bool sendEmergencyToFirebase(String path)
{
  Serial.println("Se envia Emergencia a Firebase");
  Firebase.setInt(fbdo,path + "/Emergencia", 1);
  EmergencyPressed == false;
  return true;
}
