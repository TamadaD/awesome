/*----------------------------------------------------------
    MH-Z19 CO2センサーサンプルプログラム
    https://ja.aliexpress.com/wholesale?catId=0&initiative_id=SB_20180504151821&SearchText=MH-Z19
    https://github.com/nara256/mhz19_uart
    やってることはCO2_0.0.1と一緒
  ----------------------------------------------------------*/
 
#include <MHZ19_uart.h>
 
const int rx_pin = 4;  //Serial rx pin no
const int tx_pin = 5; //Serial tx pin no
 
MHZ19_uart mhz19;
 
/*----------------------------------------------------------
    MH-Z19 CO2 sensor  setup
  ----------------------------------------------------------*/
void setup() {
  Serial.begin(115200);
  pinMode(12, OUTPUT);//メッセージ用LEDなので無くても問題ありません。
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(false);
  Serial.print("MH-Z19 now warming up...  status:"); Serial.println(mhz19.getStatus());
  delay(1000);
}
 
/*----------------------------------------------------------
    MH-Z19 CO2 sensor  loop
  ----------------------------------------------------------*/
void loop() {
  int co2ppm = mhz19.getPPM();
  int temp = mhz19.getTemperature();
  digitalWrite(12, LOW);
  //CO2濃度出力
  Serial.print("co2: "); Serial.println(co2ppm);
