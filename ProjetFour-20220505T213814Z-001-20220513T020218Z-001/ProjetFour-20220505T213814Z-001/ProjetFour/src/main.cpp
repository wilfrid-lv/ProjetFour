/**
 * @file    main.cpp
 * @author  Wilfrid Le Valégant
 * @brief   verifier les classes myTemperature et myStone
 * @version 1.0
 * @date    2022-04-20
 **/

#include "myTemperature.h"
#include "myStone.h"
#include <Arduino.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 5    // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

#define DHTTYPE    DHT22 


DHT dht_sensor(DHTPIN, DHTTYPE);

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;


#define RXD2 18//16
#define TXD2 19//17
#define BAUD_RATE 115200

#include <iostream>

#include "MyButton.h"
MyButton *myButtonT4 = new MyButton();
MyButton *myButtonT5 = new MyButton();

#include "myStone.h"
MyStone *myStone;

std::string intToHexa(int value){
  char buffer[10];
  sprintf(buffer , "0x%4X", value);
  return (buffer);
};

std::string charToString(char str, std::string formatStr){
  char buffer[10];
  sprintf(buffer , formatStr.c_str(), str);
  return (buffer);
};

std::string intToString(int value, std::string formatStr){
  char buffer[10];
  sprintf(buffer , formatStr.c_str(), value);
  return (buffer);
};



//Thread qui permet de LOOPER et lire le contenu du port serie
//avec l'aide du la fonction getValidsDatasIfExists
void readStoneData() {
  datasRead rd = myStone->getValidsDatasIfExists();
  //std::cout << "GData : " << intToHexa(abs(rd.id)) << " " << rd.command << " " << rd.name << " " << rd.type << "\n";
  switch(rd.id){

      case 0x0002: { //Version
          std::cout << "GData : " << intToHexa(abs(rd.id)) << " " << rd.command << " " << rd.name << " " << rd.type << "\n";
          std::string stoneVersion = rd.name;
          std::cout << "Version : " <<  stoneVersion.c_str() << "\n";

          //std::this_thread::sleep_for(std::chrono::milliseconds(10));

          break;
          }
        case 0x1001: { //Version
          std::cout << "GData : " << intToHexa(abs(rd.id)) << " " << rd.command << " " << rd.name << " " << rd.type << "\n";
          std::string stoneVersion = rd.name;
          std::cout << "Version : " <<  stoneVersion.c_str() << "\n";

          //std::this_thread::sleep_for(std::chrono::milliseconds(10));

          break;
          }
          if(case 0x1001)//bouton nommer demarrerfour

      }

  if(rd.id<0) std::cout << "Data received ( id: : " << intToHexa(abs(rd.id)) << "  Command: " << rd.command << " Type: " << rd.type<< ")\n";
}


void setup() {

   Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  delayMS = sensor.min_delay / 1000;


  
  Serial.begin(9600);

  Serial.println("Stone serial Txd is on pin: "+String(TXD2));
  Serial.println("Stone serial Rxd is on pin: "+String(RXD2));
  myStone = new MyStone(115200, SERIAL_8N1, RXD2, TXD2);


  myButtonT4->init(T4);
  myButtonT4->autoSensibilisation(); //Trouve la sensibilité automatiquement

  myButtonT5->init(T5);
  myButtonT5->autoSensibilisation(); //Trouve la sensibilité automatiquement

  cout << std::string("Début de l'exemple Stone de base pour le ESP32")  << "\n";


  float temperature = event.temperature ;
    char buffer[64];
  
    sprintf(buffer, "%g", temperature);
            myStone->setLabel("temperature", buffer);

    myStone->setLabel("bois","Erable"); 
    delay(100);
    myStone->setLabel("type","Dur");
    delay(100);
    myStone->setLabel("origine","Us"); 
    delay(100);
    myStone->setLabel("temps","20 sec"); 
    delay(100);
    myStone->setLabel("tpmin","25°Celsius");
    delay(100);
    myStone->setLabel("titre","Température du bois");

    /*sprintf(buffer, "%g", );
            myStone->setLabel("temps", buffer);*/

}

void loop() { 

char buffer[64];
int temperatureMin = 25
    if( demarrerfour == 1)
      {
        if(temperature >= temperatureMin * 0.9 && temperature<= temperatureMin * 1.10)
          {

          }
      }
    

  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }


  readStoneData();
  int buttonActionT4 = myButtonT4->checkMyButton();
      if(buttonActionT4 > 2)  {  //Si appuyé plus de 0.2 secondes
            Serial.println("Button T4 pressed");
            if(myStone) myStone->changePage();
            }
  int buttonActionT5 = myButtonT5->checkMyButton();
      if(buttonActionT5 > 2)  {  //Si appuyé plus de 0.2 secondes
            Serial.println("Button T5 pressed");
            //Dans la version  1.2, nous allons remplacer ces lignes pour utiliser la
            //méthode getVersion()
            //char cmdFormat2[99];
            //strcpy(cmdFormat2, "ST<{\"cmd_code\":\"sys_version\",\"type\":\"system\"}>ET");
            //std::cout << cmdFormat2 << "\n";
            //myStone->writeIt((char*)cmdFormat2);
            if(myStone) myStone->getVersion();
          }
          delay(2000);
  }

  /*setlabel->*/


