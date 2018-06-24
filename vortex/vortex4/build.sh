gcc -m32 -no-pie -Wl,-z,norelro -o vortex4 vortex4.c
execstack -s ./vortex4
sudo chown jozsi:geri ./vortex4
sudo chmod 4550 ./vortex4
