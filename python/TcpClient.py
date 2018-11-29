# -*- coding: utf-8 -*-
import socket, time
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 8000))

while True:
    st = str(time.localtime())
    s.send(st.encode('utf-8'))

    ehco_back = s.recv(1024)
    print '---', ehco_back.decode('utf-8')
    time.sleep(2)

s.close()
