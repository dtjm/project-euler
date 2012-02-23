import PELib
import List

-- Test whether a number is a circular prime
-- First, check whether the number contains a 2,4,5,6,8, or 0. If the number 
-- contains any of these then it cannot be a circular prime because any number 
-- ending in one of these digits is not prime.
isCircularPrime :: Int -> Bool
isCircularPrime n
	| length (intersect [2,4,5,6,8,0] $ digits n) > 0 = False
	| otherwise = isPrime n && (isCircularPrime' (rotateIntegerR n) n)

-- Inner recursive function to check whether a number is circular prime. 
-- Takes the original starting number so we can determine the base case
isCircularPrime' :: Int -> Int -> Bool
isCircularPrime' n orig
	| n == orig = True
	| otherwise = isPrime n && isCircularPrime' (rotateIntegerR n) orig

circularPrimes :: [Int]
circularPrimes = filter isCircularPrime [2..]
