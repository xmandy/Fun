# -*- coding: utf-8 -*-
import SocketServer

class EchoServerHandler(SocketServer.BaseRequestHandler):
    def handle(self):
        conn = self.request
        print 'client addr', self.client_address

        while True:
            client_data = conn.recv(1024)
            if not client_data:
                print 'disconnect'
                break

            print client_data.decode('utf-8') , client_data
            print 'sent echo'
            conn.sendall(client_data)

if __name__ == '__main__':
    server = SocketServer.TCPServer(("10.242.140.52", 8000), EchoServerHandler)
    server.serve_forever()
            
