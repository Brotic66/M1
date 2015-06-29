(load "lisp2li.lisp")

(defun myEval (expr)
  (eval-li (lisp2li expr ()) ()))

(defun eval-li (expr env)
  (case (car expr)
    (:LIT (cdr expr))
    (:VAR (aref env (cdr expr)))
    (:SET-VAR (setf (aref env (cadr expr)) (eval-li (cddr expr))))
    (:IF (if (eval-li (second expr) env)
            (eval-li (third expr) env)
            (eval-li (fourth expr) env)))
    (:CALL (apply (second expr) (map-eval-li (cddr expr) env)))
    (:MCALL (let ((fun (get-defun (second expr))))
            (eval-li (cdr fun)
                    (make-env-eval-li (car fun)
                    (cddr expr) env))))
    (:PROGN (map-eval-li-progn (cdr expr) env))
    (:UNKNOWN (let ((newExpr (lisp2li (second expr) (cddr expr))))
                    (if (eq (car newExpr) ':unknown)
                      (error "Fonction inconnue ~s" (second expr))
                      (eval-li newExpr env))))))

(defun map-eval-li (lexpr env)
  (if (null lexpr)
      ()
    (cons (eval-li (car lexpr) env) (map-eval-li (cdr lexpr) env))))


;; Effectue les évaluation des expr de :PROGN.
;; La différence est que progn éxécute tout mais ne renvoi que la valeur de la dernière éxécution.

(defun map-eval-li-progn (expr env)
  (if (null (cdr expr))
    (eval-li (car expr) env)
    (progn
      (eval-li (car expr) env)
      (map-eval-li-progn (cdr expr) env))))


;; Retourne un tableau de taille taille + 1 avec les valeur de départ des variable de notre environement.
;; à vérifier : premier indice 0 ou 1 (ici 1) (aref tableau 0) => NIL

(defun make-env-eval-li (taille args oenv)
   (map-eval-li-array  args oenv 1 (make-array (+ taille 1))))


;; Retourne le tableau passé en parametre rempli avec val
;; i est l'indice de départ.

(defun map-eval-li-array (args oenv pos nenv)
  (if (null args)
    nenv
    (progn
        (setf (aref nenv pos) (eval-li (car args) oenv))
        (map-eval-li-array (cdr args) oenv (+ 1 pos) nenv))))

(myEval '(defun fact (x) (if (< x 1) 1 (* x (fact (- x 1))))))
(myEval '(defun fibo (x) (if (<= x 1) x (+ (fibo (- x 1))(fibo (- x 2))))))
