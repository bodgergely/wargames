gcc -m32 --no-pie -O0 -g -o main.o -c main.c
gcc -m32 -O0 main.o setreuid.o -o main
sudo chown jozsi:geri ./main
sudo chmod 4550 ./main

