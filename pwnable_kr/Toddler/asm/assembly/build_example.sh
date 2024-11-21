gcc -c read_write_file.s
gcc -o main.o -c main.c
gcc main.o read_write_file.o -o example
sudo chown jozsi:remnux ./example
sudo chmod 4750 ./example
