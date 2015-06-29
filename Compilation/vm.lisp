;Welcome to VM in LISP
;Dans un premier temps, il faut créer la vm, c'est a dire de créer :
	;Un tableau pour simuler la pile contenant les instructions a exécutés (dans le bon ordre)
	;Un tableau pour simuler la pile de calcul en cours 
	;Un tableau pour stocker les envirronnements des fonctions appellées
	;Un tableau hash code pour stocker le code compilé
;Dans un second temps, il faut charger le code dans la vm, c'est a dire compiler du code lisp => li => lvm en langage machine virtuelle
;
;ensuite on execute la vm, c'est a dire que c'est l'appel d'une fonction qui prend en entrée la vm créée et la liste d'instruction compilée
(load "li2vm.lisp")


;@fonction : create-vm
;@action : Création et initialisation des composants de la machine virtuelle
(defun create-vm ()

	;la pile d'execution des instructions avec un fill-pointer qui fait office de stack pointeur. init à 0, et modifiable
	(defparameter *stack-exec* (make-array 0 :fill-pointer 0 :adjustable t))
	;la pile des données d'executions avec un fill-pointer qui fait office de stack pointeur. init à 0, et modifiable
	(defparameter *stack-data* (make-array 0 :fill-pointer 0 :adjustable t))
	;Tableau d'environnement avec un fill-pointer qui fait office de stack pointeur. init à 0, et modifiable
	(defparameter *env* (make-array 0 :fill-pointer 0 :adjustable t))
	; le tableau hash code (key : function name /values : implementation) - rapid access
	(defparameter *codehashed* (make-hash-table))

)

;Fonctions dédiées à la manipulations des piles de données / d'execution

;@Fonction : my-stack
;@Action : Réserve et attribue dans l'environnement n bloc pour les n paramètres
;@Param nombre d'arguments venant de (:STACK . nbargs)
(defun my-stack (nbArgs)
	(loop for i from (- nbArgs 1) downto 0 do
		(vector-push-extend (vector-pop *stack-data*) *env*)
	)
)

;@Fonction : my-lit
;@Action : Empile le littéralt dans la pile de calcul
;@Param : lit un littéral venant de (:LIT . valeur)
(defun my-lit (lit)
	(vector-push-extend lit *stack-data*)
)

;@Fonction : my-var
;@Action : Empile (ajoute à la fin du tableau) le paramètre param de l'environnement courant (pile de calcul) dans la pile de données 
;@Param : param, un paramètre venant de (:VAR . param)
(defun my-var (indiceparam)
	(vector-push-extend (elt *env* (- (length *env*) indiceparam)) *stack-data*)
)

;@Fonction : my-set-var
;@Action : Met à jour la variable à l'indice indiceparam de la pile de donnée avec le sommet de la pile d'execution et la dépile 
;@Param : indice param qui vient de (:SET-VAR . indiceparam)
(defun my-set-var (indiceparam) 
	(setf (aref *env* indiceparam) (vector-pop *stack-exec*))
)

;@Fonction : my-call
;@Action : Recherche de la fonction qui appel de cette dernière : depile ses paramètres et empile le résultat à la place
;@Param : Nom fonction qui vient de  : (:CALL . nomfonction)
;Si nomfonction est une fonction non élémentaire, on charge son code dans la pile d'execution. 
(defun my-call (nomfonction)

	(cond
		;Pour les fonctions élémentaires, on dépile les arguments et on remplace par le résultat
		((eq '+ nomfonction)(let ((x1 (vector-pop *stack-data*))(x2 (vector-pop *stack-data*)))(vector-push-extend (+ x2 x1) *stack-data*)))
		((eq '- nomfonction)(let ((x1 (vector-pop *stack-data*))(x2 (vector-pop *stack-data*)))(vector-push-extend (- x2 x1) *stack-data*)))
		((eq '< nomfonction)(let ((x1 (vector-pop *stack-data*))(x2 (vector-pop *stack-data*)))(vector-push-extend (< x2 x1) *stack-data*)))
		((eq '> nomfonction)(let ((x1 (vector-pop *stack-data*))(x2 (vector-pop *stack-data*)))(vector-push-extend (> x2 x1) *stack-data*)))
		((eq '<= nomfonction)(let ((x1 (vector-pop *stack-data*))(x2 (vector-pop *stack-data*)))(vector-push-extend (<= x2 x1) *stack-data*)))
		((eq '>= nomfonction)(let ((x1 (vector-pop *stack-data*))(x2 (vector-pop *stack-data*)))(vector-push-extend (>= x2 x1) *stack-data*)))
		((eq '= nomfonction)(let ((x1 (vector-pop *stack-data*))(x2 (vector-pop *stack-data*)))(vector-push-extend (= x2 x1) *stack-data*)))
		((eq '/ nomfonction)(let ((x1 (vector-pop *stack-data*))(x2 (vector-pop *stack-data*)))(vector-push-extend (/ x2 x1) *stack-data*)))
		((eq '* nomfonction)(let ((x1 (vector-pop *stack-data*))(x2 (vector-pop *stack-data*)))(vector-push-extend (* x2 x1) *stack-data*)))
		((eq 'eq nomfonction)(let ((x1 (vector-pop *stack-data*))(x2 (vector-pop *stack-data*)))(vector-push-extend (eq x2 x1) *stack-data*)))
		;Pour les fonctions compilées à appeller, on les charge dans la pile d'execution si elles existent
		((load-stack-exec nomfonction))
	)

)

;@Fonction : my-return (:RTN)
;@Action : On repasse dans l'était initial de la pile d'exécution avant l'appel, donc on défait dans l'environnement les args de la fonction
(defun my-return ()
	(vector-pop *env*)
)

;@Fonction : my-skip
;@Action : saute nbinstr dans la pile d'exécution (donc on dépile jusquà arriver ou l'on veut)
;@Param : nbinsrt qui vient de (:SKIP . nbinstr)
(defun my-skip (nbinstr)
	(loop for i from (- nbinstr 1) downto 0 do
		(vector-pop *stack-exec*)
	)
)

;@Fonction : my-skipil 
;@Action : saute nbinstr ssi le sommet de la pile de données (de calcul) donc résultat d'une comparaison rend nil par ex) et dépile cette valeur au sommet
;@Param : nbinsrt qui vient de (:SKIPNIL . nbinstr)
(defun my-skipnil (nbinstr)
	(if (eq (vector-pop *stack-data*) nil) (my-skip nbinstr))
)

;@Fonction : my-skiptrue
;@Action : saute nbinsrt ssi le sommet de la pile de données (de calcul) donc résultat d'une opération logique rend 1 par ex et dépile cette valeur au sommet
;@Param :
(defun my-skiptrue (nbinstr)
	(if (eq (vector-pop *stack-data*) 1) (my-skip nbinstr))
)


;@Fonction : load-vm
;@Action : précompilation du code LISP en LI (langage intermédiaire) puis compilation de LI à VM (langage machine)
(defun load-vm (expr)
	(let 	((codeloaded (li2vm (lisp2li expr () ) ())));compilation
			(setf (gethash (car codeloaded) *codehashed*) (cdr codeloaded));chargement clé : nom fonction. Valeur : code fonction
	)
)

;@Fonction : load-stack-exec
;@Action : Chargement de la pile d'exécution par la fonction (nom de cette fonction passée en paramètre)
;@Return : message d'erreur si fonction n'existe pas dans l'environnement 
(defun load-stack-exec (nomfonction) ;fonction de chargement de la pile d'execution dans la machine virtuelle

	(if (gethash nomfonction *codehashed*) ;On regarde si la fonction appellée existe dans le code compilé 
		(loop for i from (- (length (gethash nomfonction *codehashed*)) 1) downto 0 do 
			(vector-push-extend (elt(gethash nomfonction *codehashed*) i) *stack-exec*) ;Agrandit le tableau ajustable qui fait office de pile d'exécution et y ajoute le code (qui n'est plus haché) 
			;Attention ! On empile à l'envers pour que le return se retrouve en bas et pour que les appels reccursifs s'empile vers le haut (fin du tableau) et se dépile vers le bas (début du tableau)
		)
		(print "Erreur : la fonction demandée est inconnue !") ; si elle existe pas
	)

)

;@Fonction : load-env
;@Action :  chargement de l'environnement avec le(s) param(s) d'une fonction appellée
(defun load-env (param)
	(vector-push-extend param *env*)
)

;@Fonction : run-vm
;@Action : Lecture instruction/instruction de la pile d'execution, traitement des calculs (analyse par cas et dispatch)
(defun run-vm ()
	(let ((instruction (vector-pop *stack-exec*)))
		(cond
			;On execute l'action voulue et on passe à l'instruction suivante
			((eq ':LIT (car instruction)) (progn (my-lit (cadr instruction)) (run-vm)) )
			((eq ':VAR (car instruction)) (progn (my-var (cadr instruction)) (run-vm)) )
			;((eq ':SET-VAR (car instruction)) (progn (my-set-var (cadr instruction)) (run-vm)) ) ;pas besoin ?
			((eq ':STACK (car instruction)) (progn (my-stack (cadr instruction)) (run-vm)) )
			((eq ':CALL (car instruction)) (progn (my-call (cadr instruction)) (run-vm)) )
			((eq ':SKIP (car instruction)) (progn (my-skip (cadr instruction)) (run-vm)) )
			((eq ':SKIPNIL (car instruction)) (progn (my-skipnil (cadr instruction)) (run-vm)) )
			;((eq ':SKIPTRUE (car instruction)) (progn (my-skiptrue (cadr instruction)) (run-vm)) ) ;pas besoin ?
			;Si retour final ou retour intermédiaire (appel réccursif)
			((eq ':RTN (car instruction)) (progn (my-return) (if (eq (length *stack-exec*) 0) (vector-pop *stack-data*) (run-vm))))
		)

	 )

)

;@Fonction : execute-vm
;@Actions : Associe expr à une fonction chargée dans la VM et l'exécute si présente (et si nb arg correspond bien)
;1- Chargement de la fonction dans la pile d'execution (load-stack-exec)
;2- Liaison paramètres formels / arguments (load-env)
;3- Exécution si ok (run-vm)
(defun execute-vm (expr) ;fonction d'execution du code dans la vm et retourne un resultat en fonction de l'appel donné
;utiliser peut etre &rest après pour mieux gérer le nb d'arguments
	(progn
		;Première action : on charge dans la pile d'execution le corps de la fonction si elle existe
		(load-stack-exec (car expr))
		(if (eq (cadr (vector-pop *stack-exec*)) (length (cdr expr))) ;On regarde si l'argument du stack est égal à la taille du reste des arguments
			(load-env (cadr expr)) ;Deuxième action :Si ok alors on inscrit dans l'environnement la valeur du parametre demandé
			(print "Le nombre d'arguments passés est incorrect !");Sinon appel incorrect
		)
		(run-vm);Troisième action : on commence l'execution
	)

)

;@Fonction "principale" permettant d'exécuter une fonction dans la machine virtuelle
;@Action :
;1 - Creation/Initialisation de la VM
;2 - Chargement d'une fonction dans la VM
;3 - Execution de la fonction par la VM et affichage du résultat.
(defun vm ()
	(print "on initialise la memoire...")
	(create-vm) ;On initialise
	(print "on charge le code a compile...")
	(load-vm '(defun fibo (x) (if (<= x 1) x (+ (fibo (- x 1))(fibo (- x 2)))))) ;On charge
	(print "et maintenant on execute !")
	(print (execute-vm '(fibo 11))) ;On execute et on affiche. ca affiche deux fois comme ça
)