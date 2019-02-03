# -*- coding : utf-8 -:-

# import
import time
from websocket import create_connection

# 関数定義
ws = create_connection ('ws://192.168.0.116:1234/')
result = ws.recv ()

print ('Recieved"%s"' % result)


def main():
    tp, rh, ir, co2ppm = 1, 2, 3, 5

    ws.send (str(tp) + ',' + str(rh) + ',' + str(ir) + ',' + str(co2ppm))

    ws.close ()


while True:
    main()
    time.sleep(1)
