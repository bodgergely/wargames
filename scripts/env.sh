export TEMPDIR=`mktemp -d` && cd $TEMPDIR
touch bashrc
echo "alias ls='ls -lha'" >> bashrc
echo "alias vim='vim -u vimrc'" >> bashrc
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
# creating gdbscript
touch gdbscript
echo "set disassembly-flavor intel" >> gdbscript
echo "b main" >> gdbscript
echo "layout asm" >> gdbscript
echo "focus asm" >> gdbscript
echo "run" >> gdbscript
echo "si" >> gdbscript
echo "ni" >> gdbscript
alias gdb_asm='gdb --command gdbscript --args'