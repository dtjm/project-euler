module Main where
import PELib

-- get diagonals for an nxn square
diagonals n
	| odd n && n > 0 = diag' 1 n 0 0
	| otherwise = []

--diag' currentLevel endLevel currentCorner(1-4) prevElement

diag' 1 1 _ _ = [1]
diag' 1 e _ p = 1 : (diag' 3 e 1 1)
diag' c e 4 p 
	| c == e    = [next] -- stop on the 4th element of the last level
	| otherwise = next : (diag' (c+2) e 1 next)
	where next = p + (c-1)
diag' cL eL corner prev = next : (diag' cL eL (corner+1) next)
	where next = prev + (cL-1)
