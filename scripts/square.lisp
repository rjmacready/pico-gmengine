(print "loading square")

(defclass block (game-object square physical)
  ((color :initform (get-color 0 255 0))))

(print "square loaded")