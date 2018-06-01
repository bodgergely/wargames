gcc -m32 --no-pie -O0 -g -o example.o -c example.c
gcc -m32 -O0 example.o setreuid_cat.o -o example
sudo chown jozsi:geri ./example
sudo chmod 4550 ./example

