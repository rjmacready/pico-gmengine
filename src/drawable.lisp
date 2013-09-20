
(defclass drawable () ())
(defmethod on-draw ((this drawable))
  (error "(draw drawable) is not defined!"))

(defclass circle (drawable) 
  ((x :initarg :x) 
   (y :initarg :y) 
   (radius :initarg :radius) 
   (color :initarg :color)))

(defmethod on-draw ((this circle))
  ;(print "draw circle")
  (with-slots (x y radius color) this
    ;(print x)
    ;(print y)
    ;(print radius)
    ;(print color)
    (draw-circle :screen x y radius color)))

;(defclass bmp-drawable (drawable)
;  ((bitmap-name)))

;(defmethod draw ((this bmp-drawable))
;  nil)

