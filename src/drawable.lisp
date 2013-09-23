
(defclass drawable () ())
(defmethod on-draw ((this drawable))
  (error "(draw drawable) is not defined!"))

; low level wrapper for SDL_Surface
(defclass raw-surface (drawable)
  ((surface :initarg :surface)))

(defmethod on-draw ((this raw-surface))
;  (print 'draw-raw-surface)
  (with-slots (surface x y) this
;    (print `(with slots ,x ,y ,surface))
    (draw-surface :screen (floor x) (floor y) surface nil)))

(defclass circle (drawable) 
  ((x :initarg :x) 
   (y :initarg :y)
   (radius :initarg :radius) 
   (color :initarg :color)))

(defmethod on-draw ((this circle))
  (with-slots (x y radius color) this
    (draw-circle :screen (floor x) (floor y) radius color)))

(defclass square (drawable)
  ((x :initarg :x)
   (y :initarg :y)
   (height :initarg :height)
   (width :initarg :width)
   (color :initarg :color)))

(defmethod on-draw ((this square))
  (with-slots (x y height width color) this
    (draw-rect :screen (floor x) (floor y) (floor width) (floor height) color)))
