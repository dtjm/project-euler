import PELib
import Data.List

isPdInt :: Int -> Bool
isPdInt n = isPdStr (show n)

isPdStr :: [Char] -> Bool
-- isPdStr [] = True
isPdStr xs = isPdStr' (sort xs)
	where 	isPdStr' [] = True
		isPdStr' xs = (last xs == (head.show.length) xs) &&
	  		 isPdStr' (init xs)

isPdIntTriple (a, b, c) = isPdStr ((show a) ++ (show b) ++ (show c))

isPdProduct n = or [isPdIntTriple(x, n `div` x, n) | 
			x <- (filter (< (ceiling (sqrt (fromIntegral n)))) (divisors n))]

is9PdProduct n = or [ (length ((show x) ++ (show (n `div` x)) ++ (show n))) == 9 && 
		      isPdIntTriple(x, n `div` x, n) | 
				x <- (filter (< (ceiling (sqrt (fromIntegral n)))) (divisors n))]

main = do print (sum (filter is9PdProduct [1..9876]))
