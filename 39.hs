import PELib

solutions :: Int -> [[Int]]
solutions n = [ [a,b,c] | a <- [1..(div n 2) + 1], b <- [a..(div n 2) + 1], c <- [n-a-b], a*a+b*b==c*c]

allSolutions = map solutions [0..]

