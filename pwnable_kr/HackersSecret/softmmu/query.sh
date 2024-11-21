DR=/proc/softmmu
rm phys
cat virt | \
while read CMD
do
    echo -ne $CMD
    echo -ne $CMD > $DR ; hexdump -C $DR | head -n 1 >> phys
done

cat phys
