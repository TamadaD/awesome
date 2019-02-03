# -*- coding : utf-8 -:-

# import
import time
from websocket import create_connection

# 関数定義
ws = create_connection ('ws://192.168.0.116:1234/')
result = ws.recv ()

print ('Recieved"%s"' % result)


i = 0
while True:
    tp, rh, ir, co2ppm = i, 2, 3, 6
    ws.send (str(tp) + ',' + str(rh) + ',' + str(ir) + ',' + str(co2ppm))
    i += 1
    time.sleep(1)


