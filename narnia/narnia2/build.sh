gcc -m32 -ggdb -o narnia2 narnia2.c
sudo chown jozsi:geri narnia2
sudo chmod 4550 narnia2
sudo execstack -s narnia2
