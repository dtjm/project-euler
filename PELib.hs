module PELib (
	isPrime,
	primes, 
	divisors, 
	fac,
	choose,
	digits,
	rotateIntegerR )
where
import Data.List (nub)
import Data.Char (digitToInt)

isPrime :: Int -> Bool
isPrime x = elem x (take x primes)

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

-- Calculate the factorial of an integer
fac :: Int -> Integer
fac = 	let	fac' 0 = 1
		fac' 1 = 1
		fac' n = n * fac' (n-1)
	in 	(map fac' [0..] !!)

choose n k = (fac n) `div` (fac k) `div` (fac (n-k))

-- converts a number to a list of digits
digits :: Int -> [Int]
digits n = map digitToInt ( show n )

-- Rotate a list to the right (last element gets placed first)
rotateListR (xs) = last xs : init xs

-- Rotate an integer to the right
rotateIntegerR :: Int -> Int
rotateIntegerR n = read $ rotateListR $ show n
