(print "loading cheela")

;(load "/home/user/mini-game-engine/src/gameobjects.lisp")
;(load "/home/user/mini-game-engine/src/drawable.lisp")
;(load "/home/user/mini-game-engine/src/game.lisp")

(defclass cheela (game-object circle)
  ())

(defmethod on-update ((this cheela))
  (with-slots (x) this
    (setf x (+ (mod (+ x 1) 100) 10))))

(print "cheela loaded")