sudo rm ./narnia1
gcc -m32 --no-pie -g -o narnia1 narnia1.c
sudo chown jozsi:geri ./narnia1
sudo chmod 4750 ./narnia1
sudo execstack -s ./narnia1
