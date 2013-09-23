; simple "presention detection" (very-poor-man's collision detection / raycasting)

(defclass physical ()
  (x y))

(defmethod are-you-at-p ((this physical) p-x p-y who)
  (with-slots (x y) this
    (and (= p-x x) (= p-y y))))

