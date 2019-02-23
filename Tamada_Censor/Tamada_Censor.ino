#include <Wire.h>

#define DEV_ADR 0x5c  // AM2320スレーブアドレス
#define PWM_PIN 8
#define masterdelay 100

int val = 4;
int timer = 0;
int pin2 = 0 ;
int date[100];
int all = 0;
int ir = all/1000;
int prev_val = LOW;

uint8_t data[8];

float rh = ((float)(data[2]*256+data[3]))/10; // 湿度
float tp = ((float)(data[4]*256+data[5]))/10; // 温度

long high_level_start = 0L;
long high_level_end = 0L;
long low_level_start = 0L;
long low_level_end = 0L;
long time_high = high_level_end - high_level_start;
long time_low = low_level_end - low_level_start;
long co2ppm = 5000 * (time_high - 0.002) / (time_high + time_low - 0.004);

void setup() {

    Wire.begin();
    Serial.begin(9600);
    pinMode(PWM_PIN, INPUT);

}

void loop() {

int prev_val = LOW;
long high_level_start = 0L;
long high_level_end = 0L;
long low_level_start = 0L;
long low_level_end = 0L;

  long cycle_start_time = millis();
  int pin_in = digitalRead(PWM_PIN);

  if (pin_in == HIGH) {
    if (prev_val == LOW) {
      long time_high = high_level_end - high_level_start;
      long time_low = low_level_end - low_level_start;
      long co2ppm = 5000 * (time_high - 0.002) / (time_high + time_low - 0.004);
      Serial.println("PPM = " + String(co2ppm));

      high_level_start = cycle_start_time;
      prev_val = HIGH;
    } else {
      high_level_end = cycle_start_time;
    }
  } else {
    if (prev_val == HIGH) {
      low_level_start = cycle_start_time;
      prev_val = LOW;
    } else {
      low_level_end = cycle_start_time;
    }
  }



        uint8_t data[8];

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
  }



int ir = analogRead(A0) ;

 float rh = ((float)(data[2]*256+data[3]))/10; // 湿度
    float tp = ((float)(data[4]*256+data[5]))/10; // 温度

long co2ppm = 5000 * (time_high - 0.002) / (time_high + time_low - 0.004);

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
