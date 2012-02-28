import PELib
import Data.List

isPandigital :: [Char] -> Bool
isPandigital n = sort n == "123456789"

concatNums :: [Int] -> [Char]
concatNums [] = []
concatNums (x:xs) = show x ++ concatNums xs

multiples n = [ n * i | i <- [1..] ]
concatMultiples :: Int -> [[Char]]
concatMultiples n = [ concatNums (take i $ multiples n) | i <- [1..] ]

candidates :: Int -> [[Char]]
candidates n = filter (\x->isPandigital x) $ takeWhile (\y -> length y <= 9) (concatMultiples n)

allCandidates = concatMap candidates [2..10000]

