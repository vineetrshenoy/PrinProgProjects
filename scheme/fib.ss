#lang racket
(define fib (lambda (x)
	(cond ((= x 1) 1)
		((= x 2) 1)
		(else (+ (fib (- x 1)) (fib (- x 2)))))))