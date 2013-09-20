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

