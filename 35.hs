import PELib

isCircularPrime :: Int -> Bool
isCircularPrime n = isPrime n && (isCircularPrime' (rotateIntegerR n) n)

isCircularPrime' :: Int -> Int -> Bool
isCircularPrime' n orig
	| n == orig = True
	| otherwise = isPrime n && isCircularPrime' (rotateIntegerR n) orig

circularPrimes :: [Int]
circularPrimes = filter isCircularPrime [2..]
