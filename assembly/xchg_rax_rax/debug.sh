set -e
./assemble.sh 
./link.sh
gdb --command gdb_asm.gdb --args ./hello

