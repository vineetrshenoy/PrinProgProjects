#lang racket
(define ll '((a) ((b) (c d) (((e))))))

(define p11list
  (cons 'a (cons '(b c) (cons 'd (cons (cons '(e f) (cons '(g)'())) '())))))


(define concat(lambda (x)
	(cons (car (getValue x)) '(b))))


(define getValue(lambda (x)
	(if (not (pair? (car x)))
		x
		(getValue(car x)))))

(define ptest 
	(car ll))
	