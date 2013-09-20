
; init game instance, run on-startup
(defparameter *game* nil)

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
  (loop for x in (slot-value *game* 'game-objects) do (on-update x)))

(defun run-ondraw ()
  (loop for x in (slot-value *game* 'game-objects) do (on-draw x)))
