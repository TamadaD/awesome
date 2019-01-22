int val = 4;
int tp = 1;
int rh = 2;
int ir = 3;
int co2ppm = 4;

void setup() {
  Serial.begin(9600);

}

void loop() {
  
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
