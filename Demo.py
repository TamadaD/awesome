#import
import time

while True:
    values = [100,100,100,100]

    tp = values[0]/10
    rh = values[1]/10
    ir = values[2]/10
    co2ppm = values[3]/10
        
    print(str(tp) +"℃"+ str(rh) +"%" +str(ir) + str(co2ppm) + "%")
time.sleep(1)

