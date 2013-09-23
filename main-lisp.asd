(defsystem "main-lisp"
  :components ((:file "src/drawable")
	       (:file "src/simplephy")
	       (:file "src/gameobjects" :depends-on ("src/drawable"))
	       (:file "src/game")
	       (:file "src/main-lisp" :depends-on ("src/simplephy"
						   "src/gameobjects"
						   "src/drawable"
						   "src/game"))))
