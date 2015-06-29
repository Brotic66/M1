(load "lisp2li.lisp")

(defun li2vm (expr env)
	(cond
		(
			(eq (car expr) :LIT) 
			(li2vm-lit (cdr expr))
		)
		(
			(eq (car expr) :VAR) 
			(li2vm-var (cdr expr))
		)
		(
			(eq (car expr) :IF)
			(li2vmif expr env)
		)
		(
			(eq (car expr) :CALL)
			(li2vm-call expr env)
		)
		(
			(eq (car expr) :UNKNOWN)
			(li2vm-unk expr env)
		)
		(
			(eq (car expr) 'SET-DEFUN)
			(li2vm-defn expr env)
		)

	)
)

;lit bon
(defun li2vm-lit (expr)
	; Ici on recuperer (:LIT X) avec X un literal
	(if (eq expr nil)
		()
		;On ajoute l'expression a la liste des appels.
		(list (list :LIT expr))
	)
)

;var bon
(defun li2vm-var (expr)
	(if (eq expr nil)
		()
		(list (list :VAR expr))
	)
)

;correct fini
(defun li2vmif (expr env)
	; (:IF (:CALL > (:LIT 3) (:LIT 5))
		;(:LIT 4)
		;(:LIT 6)
	;)
	(if (eq nil expr)
		()
		(append
			(li2vm (cadr expr) env)
			(list (list :SKIPNIL (+ 1 (length (li2vm (caddr expr) env)))))
			(li2vm (caddr expr) env)
			
			(list (list :SKIP (length (li2vm (cadddr expr) env))))
			(li2vm (cadddr expr) env)
			(list (list :RTN))

		)
	)
)

;call fini
(defun li2vm-call (expr env)
	;(print "Call appelle sur : ")
	;(print expr)

	;(:CALL + (:LIT . 1) (:LIT .2))
	; OU
	;(:CALL SET-DEFUN (:LIT . FIBO) ....)
	(if (eq 'SET-DEFUN (cadr expr))
		(li2vm (cdr expr) ())
		(append
			(li2vm (caddr expr) env)
			(li2vm (cadddr expr) env)
			(list (list :CALL (cadr expr)))
		)
	)
)

;On recoit :
;SET-DEFUN (:LIT . FIBO) (:LIT . 2 :IF .....)
(defun li2vm-defn (expr env)

	; /!\ PRINT POUR DEBUG : 
	; Print de ce qu'on recoit
	; Print du nombre de parametres
	; Print du reste du code 

	;(print "DEFN appelle sur : ")
	;(print expr)
	;(print (car (cdar (cddr expr))))
	;(print (cddr (car (cddr expr))))
	;(print (cdadr expr))
	(append
		; on colle le nom de la fonction de debut a lancer
		(cons (cdadr expr) ())
		
		(list (list ':STACK (- (car (cdar (cddr expr))) 1)))
		; on va chercher le 2, on fait - 1 pour savoir le nombre de params. pour le stack
		(li2vm (cddr (car (cddr expr))) env)
		; on li2vm le reste du code.
	)
)

(defun li2vm-unk (expr env)
	; /!\ PRINT POUR DEBUG : 

	;(print "UNKNOWN appelle sur : ")
	; Tout ce qu'on recoit : 
	; Exemple !! : (:UNKNOWN (FIBO (- X 2)) (X . 1))
	;(print expr)

	;Code a retraiter dans lisp2li
	;(print (cadadr expr))
	
	; ENvironnement a repasser
	;(print (cddr expr))
	
	;nom de la fonction pour le call
	;(print (caadr expr))
	

	(append  
		; on va traiter tout le code inconnu. On passe l'environne
		(li2vm (lisp2li (cadadr expr) (cddr expr)) ())
		; on recolle un :Call avec le nom de la fonction.
		(list (list :call (caadr expr)) )
	)
)


;(print (li2vm '(:CALL SET-DEFUN (:LIT . FIBO)  (:LIT 2 :IF (:CALL <= (:VAR . 1) (:LIT . 1)) (:VAR . 1)   (:CALL + (:UNKNOWN (FIBO (- X 1)) (X . 1)) (:UNKNOWN (FIBO (- X 2)) (X . 1))))) ()))
(print (li2vm (lisp2li '(defun fibo (x) (if (<= x 1) x (+ (fibo (- x 1))(fibo (- x 2))))) ()) ()))
; meme chose, mais au cas ou..


;(defun fibo (x) (if (<= x 1) x (+ (fibo (- x 1))(fibo (- x 2)))))