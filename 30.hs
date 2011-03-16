module Main where
import Data.Char

isSumOfDigitsToPower exp n = n == sumOfDigitsToPower n exp
	where sumOfDigitsToPower n exp = sum $ map (^ exp) (digits n)

digits n = map digitToInt (show n)

terms = tail $ filter (isSumOfDigitsToPower 5) [1..upBound]

upBound = (fst.maximum) $ takeWhile f [ (9^5*d,d) | d <- [1..] ]
	  where f x = (length . digits) (fst x) >= snd x

main = do print $ sum terms
