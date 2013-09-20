
(defmethod on-startup ((this game))
  (print "this is an overload of the default on-startup")
  this)
