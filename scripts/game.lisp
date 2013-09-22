(print "loading game")

(load "/home/user/mini-game-engine/scripts/cheela.lisp")

(defparameter *deja-vu-sans* nil)
(defparameter *text* nil)

(defmethod on-startup ((this game))
  (print "this is an overload of the default on-startup")
  (print "")
  
  (setf *deja-vu-sans* (load-font "DejaVuSans.ttf" 27))
  
  (setf *text* (make-instance 'surface-game-object :x 200 :y 200 :surface 
			      (rendertext-solid *deja-vu-sans* "hello world" 255)))
  
  (with-slots (game-objects) this
    (push *text* game-objects)
    (push (make-instance 'cheela :x 10 :y 10 :radius 10 :color 255) game-objects))

  (print "Added a cheela to game.")
  this)

(print "game loaded")