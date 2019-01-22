//--------------------------------------------------
//  焦電人感センサでLチカする，ついでにシリアル通信
//   A0
//-------------------------------------------------
//  IRに入力がある=0
//  IRに入力がない=630
//------------------------------------------------

int pin2 = 0 ;

void setup(){
  /* LEDに接続した13番ピンを出力ピンに設定 */
  pinMode(13, OUTPUT);

Serial.begin (9600);
  
}

void loop(){

  
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
}
