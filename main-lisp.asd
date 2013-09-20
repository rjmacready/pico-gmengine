(defsystem "main-lisp"
  :components ((:file "src/gameobjects")
	       (:file "src/drawable")
	       (:file "src/game")
	       (:file "src/main-lisp" :depends-on ("src/gameobjects"
						   "src/drawable"
						   "src/game"))))
