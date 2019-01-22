/*----------------------------------------------------------------------
　　全部のセンサー動かして，シリアル通信
---------------------------------------------------------------------- */


#include <Wire.h>
//    #include <MHZ19_uart.h>

#define DEV_ADR 0x5c  // AM2320スレーブアドレス

uint8_t data[8];
const int rx_pin = 8;  //Serial rx pin no
const int tx_pin = 10; //Serial tx pin no
int pin2 = 0;
int all  = 0;
int val  = 4;

//  MHZ19_uart mhz19;

void setup() {
  
  Wire.begin();            
//  mhz19.begin(rx_pin, tx_pin);
//  mhz19.setAutoCalibration(false);
  Serial.begin(9600);
  delay(500);
}

void loop() {

  //   int co2ppm = mhz19.getPPM();
  int co2ppm = 50;
 //   int temp = mhz19.getTemperature();
  int date[1000];

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

int ir = all/1000;
    
  if (Wire.available() >= 8) {
    for (uint8_t i=0; i<8; i++) 
    {
      data[i] = Wire.read();
    }
   
    int rh = ((int)data[2]*256+data[3])*10; // 湿度
    int tp = ((int)data[4]*256+data[5])*10; // 温度
  
      int valu[val] = {tp,rh,ir,co2ppm};    //リストの制作
    
        for(int j=0;j<val;j++)
        {
        int high = (valu[j] >> 7)&127;
        int low  = valu[j]&127;




        Serial.write(128+j);//raspberry pi 用のデータ送信
        Serial.write(high);
        Serial.write(low);  
          }
  
  }
  delay(1000);
}
 
