for n in $(seq 4 8)
do
    num='\x0'$n'\x80\x04\x08'
    printf "%s\n" $num
    echo -ne $num > /proc/softmmu
    hexdump -C /proc/softmmu | tail -n 2
done
