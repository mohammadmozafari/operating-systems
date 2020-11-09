import socket as sc

host = ''
port = 12354
s = sc.socket(sc.AF_INET, sc.SOCK_STREAM)
s.connect((host, port))

print('connection to 12345')
message = 'hello world'
while True:
    s.send(message.encode('ascii'))
    data = s.recv(1024)
    print('recieved form server: ', str(data.decode('ascii')))
    answer = input('\ndo you want to continue (y/n): ')
    if answer == 'y':
        continue
    else:
        break
s.close()
