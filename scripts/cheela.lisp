(print "loading cheela")

;(load "/home/user/mini-game-engine/src/gameobjects.lisp")
;(load "/home/user/mini-game-engine/src/drawable.lisp")
;(load "/home/user/mini-game-engine/src/game.lisp")

(defclass cheela (game-object circle)
  ())

(defmethod on-update ((this cheela))
  ;(print "cheela on-update")
  nil)

(print "cheela loaded")