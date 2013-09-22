(print "loading cheela")

(defclass cheela (game-object circle)
  ((_time :initform nil)
   (_i :initform 0)))

(defmethod move-up ((this cheela))
  (with-slots (y) this
    (when (> y 10)
      (setf y (- y 20)))))

(defmethod move-down ((this cheela))
  (with-slots (y) this
    (setf y (+ y 20))))

(defmethod move-left ((this cheela))
  (with-slots (x) this
    (when (> x 10)
      (setf x (- x 20)))))

(defmethod move-right ((this cheela))
  (with-slots (x) this
    (setf x (+ x 20))))

(defparameter *actions*
  (list #'move-down #'move-right #'move-up #'move-left)) ; 1));  

(defmethod on-update ((this cheela))
;  (declare (special *time*))
  (with-slots (_time _i) this
    (if (null _time)
	(setf _time *time*)
	(when (> (- *time* _time) 1)
	  (progn 
	    (setf _i (random (1- (length *actions*))))
;	    (print _i)

	    (funcall (nth _i *actions*) this)
	    ;(setf _i (mod (1+ _i) 4))

	    (setf _time *time*))))
    ;(print x)
    ;(print y)
    ;(print _time)
  ;  (print t)
    ;(print *time*)
;    )
))
;  (with-slots (t) this
 ;   (if (null t)
;	T
;	nil
;	(setf t *time*)
;	(when (> (- *time* t) 10)
;	  (print 1)
;	  (setf t *time*))
;	)
  ;  )
  

;  (with-slots (x) this
;    (setf x (+ (mod (+ x 1) 100) 10))))

(print "cheela loaded")