#lang racket
(define p11list
  (cons 'a (cons '(b c) (cons 'd (cons '() (cons '(e f) (cons '(g)'())))))))



(define (flatten x)
  (cond ((null? x) '())
        ((pair? x) (append (flatten (car x)) (flatten (cdr x))))
        (else (list x))))

(define delete (lambda (x l) 
  (cond ((null? l) '())
        ((pair? l) (cons (delete x (car l)) (delete x (cdr l))))
        ((equal? x l) '())
        (else l))))	
  
(define double
  (lambda (l)
    (cond [(null? l) '()]
          [(not (pair? (car l)))
           (cons (car l)
                 (cons (car l)
                       (double (cdr l))))]
          [else (cons (double (car l))
                      (double (cdr l)))])))


(define NewTable
  (lambda ()
    '()))

(define InsertIntoTable (lambda (entry table)
               (cons entry table)))

(define table
  (InsertIntoTable '(b (2 4 5)) (InsertIntoTable '(a 7) (NewTable))))


(define lookup (lambda (variable table)
                 (cond ((null? table) '())
                       ((equal? (car (car table)) variable) (car (cdr(car table))))
                       (else (lookup variable (cdr table))))))






(define squareVals
  (lambda (l)
    (map (lambda(x) (* x x)) l)))

(define newMax(lambda (x y)
    (cond ((<= x y) (+ 0 y))
          ((> x y) (+ 0 x)))))

(define newMin(lambda (x y)
    (cond ((<= x y) (+ 0 x))
          ((> x y) (+ 0 y)))))

(define maxSquareVal
  (lambda (l)
    (reduce newMax (squareVals l) 0)))

(define minSquareVal
  (lambda (l)
    (reduce newMin (squareVals l) 99999999)))