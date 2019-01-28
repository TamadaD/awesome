# -*- coding : utf-8 -:-

# import
import serial
import time
import csv
from datetime import datetime

# 関数定義
val_size = 4
values = [0 for x in range(val_size)]
isValids = [False for x in range(val_size)]
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=0.1)
path = 'test.csv'
fieldname = ['date', 'tp', 'ir', 'rh', 'co2ppm']

# ヘッダーの書き込み
with open(path, 'w') as f:
    writer = csv.DictWriter(f, fieldnames=fieldname)
    writer.writeheader()

f.close

# 処理
while True:
    headByte = ser.read()
    head = int.from_bytes(headByte, 'big')

    if head == 128:
        isValids = [False for x in range(val_size)]

    for i in range(val_size):

        if head == 128 + i:
            highByte = ser.read()
            lowByte = ser.read()
            high = int.from_bytes(highByte, 'big')
            low = int.from_bytes(lowByte, 'big')
            values[i] = (high << 7) + low

            if 0 <= values[i] and values[i] <= 1023:
                isValids[i] = True

    # リスト内の要素を整理、/10して元のけたに戻す
        tp = values[0]
        rh = values[1]
        ir = values[2]
        co2ppm = values[3]
        date = datetime.now()

        with open(path, 'a') as f:
            writer = csv.DictWriter(f, fieldnames=fieldname)
            writer.writerow({'date': date, 'tp': tp, 'rh': rh, 'ir': ir, 'co2ppm': co2ppm})

        f.close
        # 出力
        print(tp, '℃', rh, '%', ir,co2ppm, 'ppm')
