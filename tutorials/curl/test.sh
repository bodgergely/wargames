#!/bin/bash
NUM=$1
echo Factoring $NUM
./scrape-prime-fact.sh $NUM | python -c 'import operator; import functools; import sys; nums = sys.stdin.read().strip().split(","); nums = [int(i) for i in nums]; k = functools.reduce(operator.mul, nums); print(k)'
