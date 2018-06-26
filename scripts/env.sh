export TEMPDIR=`mktemp -d` && cd $TEMPDIR
touch bashrc
echo "alias ls='ls -lha'" >> bashrc
echo "alias vim='vim -u vimrc'" >> bashrc
echo "alias debug='gdb --command gdbscript --args'" >> bashrc
echo "alias debugvanilla='gdb --command gdbvanilla --args'" >> bashrc
source bashrc
#creating vimrc
touch vimrc
echo "set nocompatible" >> vimrc
echo "filetype on" >> vimrc
echo "filetype plugin indent on" >> vimrc
echo "filetype plugin on" >> vimrc
echo "syntax on" >> vimrc
echo "syntax enable" >> vimrc
echo "set number" >> vimrc
echo "set pastetoggle=<F3>" >> vimrc
echo "nnoremap ; :" >> vimrc
echo "nnoremap : ;" >> vimrc
echo "imap jk <esc>" >> vimrc
echo "imap kj <esc>" >> vimrc
echo "map vv 0" >> vimrc
echo "map nn <S-$>" >> vimrc
echo "map f y" >> vimrc
echo "set tabstop=4" >> vimrc
echo "set shiftwidth=4" >> vimrc
echo "set expandtab" >> vimrc

# creating gdbscript
touch gdbscript
echo "set disassembly-flavor intel" >> gdbscript
echo "set detach-on-fork off" >> gdbscript
echo "set follow-fork-mode child" >> gdbscript
echo "source /usr/local/peda/peda.py" >> gdbscript
echo "#source /usr/local/pwndbg/gdbinit.py" >> gdbscript
echo "b main" >> gdbscript
touch gdbvanilla
echo "set disassembly-flavor intel" >> gdbvanilla
echo "b main" >> gdbvanilla
echo "layout asm" >> gdbvanilla
echo "focus asm" >> gdbvanilla
#echo "set pagination off" >> gdbscript
#echo "run" >> gdbscript
#echo "si" >> gdbscript
#echo "ni" >> gdbscript
# end of gdbscript





