from socketIO_client_nexus import SocketIONamespace


def on_connect():
    print('connect')


def on_disconnect():
    print('disconnect')


def on_reconnect():
    print('reconnect')


def on_date_response(*args):
    print('on_date', args)


socketIO = SocketIO('localhost', 8081, LoggingNamespace)
socketIO.on('connect', on_connect)
socketIO.on('disconnect', on_disconnect)
socketIO.on('reconnect', on_reconnect)

# Listen
socketIO.on('date', on_date_response)
socketIO.emit('test', {'value': 'test3'})
socketIO.wait(seconds=10)
