# -*- coding : utf-8 -:-

# import
import serial
import time
import csv
from websocket import create_connection

# 関数定義
ws = create_connection ( 'ws://192.168.0.116:1234/' )
result = ws.recv ()

print ('Recieved"%s"' % result)

time.sleep (1)

# ヘッダーの書き込み
with open ( path, 'w' ) as f :
    writer = csv.DictWriter ( f, fieldnames=fieldname )
    writer.writeheader ()

f.close


def main():
    tp, rh, ir, co2ppm = 1, 2, 3, 5

    ws.send (str(tp) + ',' + str(rh) + ',' + str(ir) + ',' + str(co2ppm))

    ws.close ()

while True:
    main()

