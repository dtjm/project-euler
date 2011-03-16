module PELib (
	primes, 
	divisors, 
	fac,
	choose )
where
import Data.List (nub)

primes = primes' [2..]
	where primes' []     = []
	      primes' (x:xs) = x : primes' (filter ((/=0) . (`mod` x)) xs)

smallestFactor n = head $ dropWhile ((/=0).(mod n)) primes

factorize 1 = []
factorize n = x : factorize (n `div` x)
	where x = smallestFactor n

powerset [] = [[]]
powerset (x:xs) =  powerset xs ++ (map (x:) (powerset xs))

divisors n = (filter (/=n) . nub . map product . powerset . factorize) n 

fac :: Int -> Integer
fac = 	let	fac' 0 = 1
		fac' 1 = 1
		fac' n = n * fac' (n-1)
	in 	(map fac' [0..] !!)

choose n k = (fac n) `div` (fac k) `div` (fac (n-k))
