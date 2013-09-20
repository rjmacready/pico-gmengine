(print "loading game")

(load "/home/user/mini-game-engine/scripts/cheela.lisp")

(defmethod on-startup ((this game))
  (print "this is an overload of the default on-startup")
  (print "")
  (with-slots (game-objects) this
    (push (make-instance 'cheela :x 10 :y 10 :radius 10 :color 255) game-objects))
  (print "Added a cheela to game.")
  this)

(print "game loaded")