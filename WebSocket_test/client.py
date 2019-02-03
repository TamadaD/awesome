import time
from websocket import create_connection
from Tamada

ws = create_connection('ws://192.168.1.10:1234/')

result = ws.recv()
print('Recieved "%s"' % result)
time.sleep(1)

count = 0
while True:
    time.sleep(1)

    data1 = count + 10
    date2 = count + 20
    date3 = count + 30

    count += 1

    ws.send(str(data1)+ ',' + str(date2) + ',' + str(date3))
    result = ws.recv()
    print('Recieved "%s"' %result)

ws.close