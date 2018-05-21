#!/usr/bin/python3

for line in open('output', 'r'):
    if "You cant" not in line and "finished" not in line:
        print(line)
