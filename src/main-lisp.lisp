
(defparameter *game-objects* nil)


(defclass drawable () ())
(defmethod draw ((this drawable))
  nil)

(defclass circle (drawable) (x y radius color))
(defmethod draw ((this drawable))
  (with-slots (x y radius color)
      (draw-circle :screen x y radius color)))

(defclass bmp-drawable (drawable)
  ((bitmap-name)))

(defmethod draw ((this bmp-drawable))
  nil)


; a terrain is static.
; won't appear in game-loop logic.
; if you want something non-static, use a game object!
(defclass terrain () ())

; game-objects will be subject to game looping stuff
(defclass game-object () ())

(defmethod on-fixed-update ((this game-object))
  nil)

(defmethod on-update ((this game-object))
  nil)

; game loop
(defun run-onupdate ()
  (loop for x in *game-object* do (something x)))

; encapsules global logic
(defclass game () 
  ())

(defmethod on-startup ((this game))
  (print "default game on-startup")
  (print "this does nothing. redefine on-startup and add your logic")
  this)

; put here script probing and loading logic
(defun load-scripts ()
  (load "~/mini-game-engine/scripts/game.lisp")
  (print "All scripts were loaded")
  T)

; init game instance, run on-startup
(defparameter *game* nil)
(defun init-game ()
  (setf *game* (make-instance 'game))
  (on-startup *game*)
  T)