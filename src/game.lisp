
; encapsules global logic
(defclass game () 
  ((game-objects :initform nil)))

(defmethod on-startup ((this game))
  (print "default game on-startup")
  (print "this does nothing. redefine on-startup and add your logic")
  this)
