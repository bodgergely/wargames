#lang racket


(define (times func param count)
  (if (= 1 count)
      (func param)
      (func (times func param (- count 1)))))

(define (twice func val)
  (times func val 2))