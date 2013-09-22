; a terrain is static.
; won't appear in game-loop logic.
; if you want something non-static, use a game object!
(defclass terrain () ())

; game-objects will be subject to game looping stuff
(defclass game-object () 
  ((x :initarg :x) 
   (y :initarg :y)))

; a simple game object that interfaces a simple bitmap
(defclass surface-game-object (raw-surface game-object)
  ())

(defmethod on-fixed-update ((this game-object))
  nil)

(defmethod on-update ((this game-object))
  nil)

