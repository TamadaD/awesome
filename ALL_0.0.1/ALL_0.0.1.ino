#include <Wire.h>
#include <MHZ19_uart.h>
#define DEV_ADR 0x5c  // AM2320スレーブアドレス

uint8_t data[8];
const int rx_pin = 4;  //Serial rx pin no
const int tx_pin = 5; //Serial tx pin no
int pin2 = 0 ;
 
MHZ19_uart mhz19;

void setup() {
  pinMode(13, OUTPUT);
   Wire.begin();            
  Serial.begin(115200);
  pinMode(12, OUTPUT);//メッセージ用LEDなので無くても問題ありません。
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(false);
  Serial.print("MH-Z19 now warming up...  status:"); Serial.println(mhz19.getStatus());
  delay(1000);
}

void loop() {

  nt co2ppm = mhz19.getPPM();
  int temp = mhz19.getTemperature();
  digitalWrite(12, LOW);
  //CO2濃度出力
  Serial.print("co2: "); Serial.println(co2ppm);
    /* 入力ピン(2番)がHIGHならTrue */
    pin2 = analogRead(A0) ;  

   
    
    /* 入力ピン(2番)がHIGHならばLED点灯 */
    if (pin2<50){
        digitalWrite(13, HIGH);
         Serial.println(pin2);
    }
    /* 入力ピン(2番)がLOWならばLED消灯 */
    else{
        digitalWrite(13, LOW);
         Serial.println(pin2);
    }
    /* 10ms待機 */
    delay(10);
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
  }
  delay(1000);
}
 
