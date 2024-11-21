gcc -m32 -no-pie -Wl,-z,norelro -o vortex3 vortex3.c
execstack -s ./vortex3
sudo chown jozsi:geri ./vortex3
sudo chmod 4550 ./vortex3

