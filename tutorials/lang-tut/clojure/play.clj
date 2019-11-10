(println 
(->>
  (range 10)
  (map (fn [x] (* x x)))
  (into [])))
