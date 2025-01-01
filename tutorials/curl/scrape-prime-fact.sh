#/bin/bash
NUM=$1
./prime-factors.sh $NUM | pup 'div#answer' | grep -i -A 3 "CSV Format" | tail -n 1
