; ========== LISP2LI.LISP ===========

; REALISE PAR :
;		WARREN BANGUET
;		BRICE VICO
;		BAPTISTE LEULLIETTE
;		OLIVIER FRAPPEREAU





; ===== FONCTIONS AD HOC =====
(defun get-defun (symb)
  (get symb :defun))

(defun set-defun(symb expr)
  (setf (get symb :defun) expr))

(defun map-lisp2li (expr env)
  (if (atom expr)
      expr
    (cons (lisp2li (car expr) env) (map-lisp2li (cdr expr) env))))
; ==============================================================================================



; ===== FONCTION PERMETTANT LA CREATION DE L'ENVIRONNEMENT LOCAL A UNE FONCTION =====
(defun make-stat-env (args pos)
 (if (null args)
     ()
   (if (atom args)
     ; CAS LISTE UNIQUE
     (cons args pos)
   ; CAS LISTE MULTIPLE ==> CONSTRUCTION
   (cons (make-stat-env (car args) pos) (make-stat-env (cdr args) (+ 1 pos))))))
; ==============================================================================================



; ===== FONCTION PRINCIPALE RETOURNANT LE CODE LI ASSOCIE AU CODE LISP EXPR MUNI DE L'ENVIRONNEMENT ENV =====
(defun lisp2li (expr env)
; == CAS ATOME ==
(if (atom expr)
    ; == CAS LITTERAL ==
    (if (constantp expr)
        (cons :lit expr)
      ; == CAS VARIABLE CONNUE / INCONNUE
		(let ((curr (assoc expr env)))
        	(if curr
	     		(cons :var (cdr curr))
	     		(warn "~s n'est pas une variable" expr))))

 ; == A CE POINT EXPR EST UNE LISTE ==
  	(let ((foo (car expr)) (args (cdr expr)))
  		; == TESTS SUR LE CAR DE LA LISTE PASSEE EN PARAMETRE ==
	    (cond 
	    	; == CAS QUOTE ==
	    	((eq 'quote foo)
		  		(cons :lit (first args)))

		  	; == CAS IF ==
		 	((eq 'if foo)
		   		(list 
		   			:if
			 		(lisp2li (first args) env)
					(lisp2li (second args) env)
			 		(lisp2li (third args) env)))

		 	; == CAS CASE ==
		  	((eq 'case foo)
		   		(lisp2li (macroexpand-1 expr) env))

 			; == CAS COND == 
		   	((eq 'cond foo)
		   		(lisp2li (macroexpand-1 expr) env))

		    ; == CAS PROGN ==
		  	((eq 'progn foo)
		   		(cons 
		   			:progn 
		   			(map-lisp2li (cdr expr) env)))

		  	; == CAS DEFUN ==
		  	((eql 'defun foo)
		   	(lisp2li 
		   		(list 
			   		'set-defun 
			   		(list 
			   			'quote 
			   			(second expr))  
					(list 
					  	'quote 
					  	(cons 
					  		(+ 1 (length (third expr)))
							(if (cddddr expr)
								(cons :progn (map-lisp2li (cdddr expr) (make-stat-env (third expr) 1)))
								(lisp2li (cadddr expr) (make-stat-env (third expr) 1 ))))))
			    ()))

		   ; == CAS LET ==
		  	((eq 'let foo)
		   		(list 
		   			:let 
		   			(+ 1 (length (cdr expr))) 
		   			(map-lisp2li (cadr expr) env)))
	           	
	        
		   
		  ; == CAS MCALL ==> FONCTION DEF PAR UTILISATEUR ==
		  	((get-defun foo)
		   		(cons 
		   			:mcall 
		   			(cons foo (map-lisp2li args env))))

		   ; == CAS UNKNOWN ==> FOCNTION INCONNUE ==
		  	((not (fboundp foo))
		   		(cons 
		   			:unknown 
		   			(cons expr env)))

		   ; == CAS CALL ==> PRIMITIVE LISP OU FONCTION DEFINIE ==
		  (t(cons :call (cons (car expr) (map-lisp2li (cdr expr) env))))))))
; ================================================================================================	   





; ============================== TESTS AU LANCEMENT ================================================
;(lisp2li '(defun fact (x) (if (< x 1) 1 (* x (fact (- x 1))))) ())
