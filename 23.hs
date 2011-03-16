import Data.Set (toList, fromList)

primes = primes' [2..]
	where primes' []     = []
	      primes' (x:xs) = x : primes' (filter ((/=0) . (`mod` x)) xs)

smallestFactor n = head $ dropWhile ((/=0).(mod n)) primes

factorize 1 = []
factorize n = x : factorize (n `div` x)
	where x = smallestFactor n

powerset [] = [[]]
powerset (x:xs) =  powerset xs ++ (map (x:) (powerset xs))

removeDuplicates :: [Int] -> [Int]
removeDuplicates = (toList . fromList)

divisors n = (filter (/=n) . removeDuplicates . map product . powerset . factorize) n 

sumDivisors = (sum . divisors)

isAbundant n = (sumDivisors) n > n

abundantNumbers = [isAbundant n | n <- [1..]]

cachedIsAbundant n = last (take n abundantNumbers)

abundantAddends n = [(x, y) | 	x <- [12..(n `div` 2)], 
				y <- [(n-x)],
				cachedIsAbundant x,
				cachedIsAbundant y]

allAbundantAddends = [abundantAddends n | n <- [1..]]

cachedAbundantAddends n = last (take n allAbundantAddends)

hasAbundantAddends n = not (null (abundantAddends n))

numbersNotSumOfAbundants = filter (not . hasAbundantAddends) ([1..])

main = print (sum (takeWhile (<20162) numbersNotSumOfAbundants)) 

