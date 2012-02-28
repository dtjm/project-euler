import PELib
import List

rotateIntegerL :: Int -> Int
rotateIntegerL n = read $ rotateL $ show n

rotateL :: [a] -> [a]
rotateL (x:xs) = xs ++ [x]

-- Test whether a number is a circular prime
-- First, check whether the number contains a 2,4,5,6,8, or 0. If the number 
-- contains any of these then it cannot be a circular prime because any number 
-- ending in one of these digits is not prime.
isCircularPrime :: Int -> Bool
isCircularPrime n
	| length (intersect [0,2,4,5,6,8] $ digits n) > 0 && n > 5 = False
	| otherwise = isPrime n && (isCircularPrime' (rotateIntegerL n) n)

-- Inner recursive function to check whether a number is circular prime. 
-- Takes the original starting number so we can determine the base case
-- If the rotated number we are checking is lower than the original, then it
-- has already been calculated so we should just be able to look it up
isCircularPrime' :: Int -> Int -> Bool
isCircularPrime' n orig
	| n == orig = True
	| n < orig = isCircularPrime n
	| otherwise = isPrime n && isCircularPrime' (rotateIntegerL n) orig

circularPrimes :: [Int]
circularPrimes = filter isCircularPrime primeCandidates
