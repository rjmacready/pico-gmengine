
; init game instance, run on-startup
(defparameter *game* nil)
(defvar *time* nil)

; put here script probing and loading logic
(defun load-scripts ()
  (load "~/mini-game-engine/scripts/game.lisp")
  (print "All scripts were loaded")
  T)

(defun init-game ()
  (setf *game* (make-instance 'game))
  (on-startup *game*)
  T)

; game loop
(defun run-onupdate ()
  (handler-case 
      (with-slots (game-objects) *game*
	(loop 
	   for x in game-objects
	   do (progn
		(let ((*time* (get-universal-time)))
		  (on-update x)))))
    (T (e) (print `(error on run-update ,e)))))

(defun run-ondraw ()
  (handler-case 
      (with-slots (game-objects) *game*
;    (print (length game-objects))
	(loop for x in game-objects do (on-draw x)))
    (T (e) (print `(error on run-ondraw ,e)))))
