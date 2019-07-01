#include "I2Cdev.h"
#include "MPU6050.h"
#include <SPI.h>
#include <SD.h>

MPU6050 capteur(0x68);
int16_t ax, ay, az,gx, gy, gz;
int16_t nbrMesures = 0;
int32_t t =0;
float moyenneAx,moyenneAy,moyenneAz,moyenneGx,moyenneGy,moyenneGz;

File _42_;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  capteur.initialize();
  delay(5000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(900000);
  digitalWrite(LED_BUILTIN, LOW);
  
  t=millis();
  while(millis()-t<60000){
    capteur.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    //Serial.println("Stabilisation... "+String(millis()-t/300)+"%");
  }
  
  t=millis();
  while(millis()-t<10000){
      //Serial.println("Étalonnage... "+String((millis()-t)/100)+"%");
      capteur.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
      moyenneAx+=ax;
      moyenneAy+=ay;
      moyenneAz+=az;
      moyenneGx+=gx;
      moyenneGy+=gy;
      moyenneGz+=gz;;
      nbrMesures++;
    }
    moyenneAx/=nbrMesures;
    moyenneAy/=nbrMesures;
    moyenneAy-=16384;
    moyenneAz/=nbrMesures;
    moyenneGx/=nbrMesures;
    moyenneGy/=nbrMesures;
    moyenneGz/=nbrMesures;
    //Serial.println(String(moyenneAx)+"\t"+String(moyenneAy)+"\t"+String(moyenneAz)+"\t"+String(moyenneGx)+"\t"+String(moyenneGy)+"\t"+String(moyenneGz));
    SD.begin(4);
    SD.remove("42.txt");
}

void loop(){
  _42_=SD.open("42.txt",FILE_WRITE);
  while(millis()%100!=0){
  }
  capteur.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  _42_.println(String(ax-moyenneAx)+"\t"+String(ay-moyenneAy)+"\t"+String(az-moyenneAz)+"\t"+String(gx-moyenneGx)+"\t"+String(gy-moyenneGy)+"\t"+String(gz-moyenneGz));
  //Serial.println(String(ax-moyenneAx)+"\t"+String(ay-moyenneAy)+"\t"+String(az-moyenneAz)+"\t"+String(gx-moyenneGx)+"\t"+String(gy-moyenneGy)+"\t"+String(gz-moyenneGz));
  _42_.close();
}
