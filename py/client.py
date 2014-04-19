import socket

host = 'sdev.ubnt.com.cn'
port = 21151
size = 1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
s.send('hello')
data = s.recv(size)
s.close()
print 'recv:', data
