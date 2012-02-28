module PELib (
	isPrime,
	primes, 
	primeCandidates,
	divisors, 
	fac,
	choose,
	digits,
	rotateIntegerR )
where
import Data.List (nub)
import Data.Char (digitToInt)

merge :: [a] -> [a] -> [a]
merge (x:xs) (y:ys) = [x,y] ++ merge xs ys

isPrime :: Int -> Bool
isPrime x = elem x (takeWhile (<=x) primes)

primeCandidates = ([2,3,5] ++ (filter ((/=0) . (`mod` 5)) kplusminusone))
	where kplusminusone = (merge [6*k-1|k <- [1..]] [6*k+1|k <-[1..]])

primes = primes' primeCandidates
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
