import Data.List

allFibs = 0 : 1 : zipWith (+) allFibs (tail allFibs)

fib n = allFibs !! n

--fibsWithTerms = [(t,f) | t <- [0..],
--			 f <- fib t ]

--intLength :: Integer -> Integer
--intLength = (length . show)
