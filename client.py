# -*- coding : utf-8 -:-

# import
import time
from websocket import create_connection

# 関数定義
ws = create_connection ('ws://192.168.0.116:1234/')
result = ws.recv ()

print ('Recieved"%s"' % result)


tp, rh, ir, co2ppm = 1, 2, 3, 6
while True:
    ws.send (str(tp) + ',' + str(rh) + ',' + str(ir) + ',' + str(co2ppm))
    tp += 1
    rh += 1
    ir += 1
    co2ppm += 1
    time.sleep(1)


