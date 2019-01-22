//--------------------------------------------------
//  焦電人感センサでLチカする，ついでにシリアル通信
//  10ms間隔のデータを10s間隔で平均する
//   A0
//-------------------------------------------------
//  IRに入力がある=0
//  IRに入力がない=630
//------------------------------------------------

int pin2 = 0 ;
int date[1000];
int all = 0;

void setup(){

Serial.begin (9600);
  
}

void loop(){

for(int del=0;del<1000;del++)
  {
    pin2 = analogRead(A0) ; 
   // Serial.println(pin2);   
    date[del] = pin2;
    delay(10);

all = all+date[del];
    
  }

Serial.print (all/1000);
  
}
