from websocket_server import WebsocketServer


def new_client(client, server):
    server.send_message_to_all('Hey all, a new client has joined us')


def send_msg_all_client(client, server, message):
    server.send_message_to_all('Hey all:' + message)


server = WebsocketServer(1234, host='192.168.0.116')
server.set_fn_new_client(new_client)
server.set_fn_message_received(send_msg_all_client)

server.run_forever()
