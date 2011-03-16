module Main where
import PELib

isPrime n = n > 0 && divisors n == [1]

consecPrimes list = takeWhile isPrime list
numConsPrimes = (length . consecPrimes)

f n a b = n*n + a*n + b

primeSequence a b = consecPrimes $ 
			[ f n a b | n <- [0..] ]

flista = [ ((length $ primeSequence a b), primeSequence a b, a, b, a*b) 
		| a <- [(-999)..999],
		  b <- [(-999)..999],
		  (a > 0) || (b > 0),
		  isPrime (abs a) || (abs a) == 1,
		  isPrime (abs b) || (abs b) == 1]

flistn =  [ ((length $ primeSequence a b), primeSequence a b, a, b, a*b) 
		| a <- [(-100)..(-1)],
		  b <- [(-100)..(-1)] ]

main = do print flista
	  print $ maximum flista
