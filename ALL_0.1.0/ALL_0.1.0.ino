/*----------------------------------------------------------------------
　　全部のセンサー動かして，シリアル通信
---------------------------------------------------------------------- */


#include <Wire.h>
#include <MHZ19_uart.h>

#define DEV_ADR 0x5c  // AM2320スレーブアドレス
#define LED 13  //確認用LED

uint8_t data[8];
const int rx_pin = 4;  //Serial rx pin no
const int tx_pin = 5; //Serial tx pin no
int pin2 = 0 ;
 int date[1000];
int all = 0;

MHZ19_uart mhz19;

void setup() {
  pinMode(LED, OUTPUT);
   Wire.begin();            
  Serial.begin(115200);
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(false);
  Serial.print("MH-Z19 now warming up...  status:");
  Serial.println(mhz19.getStatus());
  delay(500);
}

void loop() {

  int co2ppm = mhz19.getPPM();
  int temp = mhz19.getTemperature();

 // AM2320センサーのウェイクアップ
  Wire.beginTransmission(DEV_ADR);
  Wire.endTransmission();
  
  // 湿度・温度データ取得要求
  Wire.beginTransmission(DEV_ADR);
  Wire.write(0x03);         // レジスタ読み取りコマンド
  Wire.write(0x00);         // 読み取り開始レジスタ番号
  Wire.write(0x04);         // 読み取りデータ数    
  Wire.endTransmission();

  // データの取得
  Wire.requestFrom(DEV_ADR,8); 
  
for(int del=0;del<1000;del++)
  {
    pin2 = analogRead(A0) ; 
   // Serial.println(pin2);   
    date[del] = pin2;
    delay(10);

all = all+date[del];
    
  }

Serial.print (all/1000);
    
  if (Wire.available() >= 8) {
    for (uint8_t i=0; i<8; i++) {
      data[i] = Wire.read();
    }
   
    float rh = ((float)(data[2]*256+data[3]))/10; // 湿度
    float tp = ((float)(data[4]*256+data[5]))/10; // 温度
    
    // 湿度・温度の表示
    Serial.print("T=");
    Serial.print(tp);
    Serial.print("c");
    Serial.print(" H=");
    Serial.print(rh);
    Serial.println("%");
    Serial.print("co2: ");
    Serial.println(co2ppm);
    Serial.println(all/1000);
  }
  delay(100);
}
 
