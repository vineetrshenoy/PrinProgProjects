#lang racket
(define sum (lambda (ls)
	(if (null? ls)
		0
		(+ (car ls) (sum (cdr ls))))))