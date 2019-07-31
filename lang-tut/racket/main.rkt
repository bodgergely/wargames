#lang racket

(define (times func param count)
  (if (= 1 count)
      (func param)
      (func (times func param (- count 1)))))

(define (twice func val)
  (times func val 2))


(define (make-add-suffix s2)
  (lambda (s) (string-append s s2)))

;(twice (make-add-suffix "!") "Marcika")
;(times (make-add-suffix "!") "Marcika" 6)

