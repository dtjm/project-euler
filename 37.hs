import PELib

sortedMerge [] [] = []
sortedMerge xs [] = xs
sortedMerge [] ys = ys
sortedMerge (x:xs) (y:ys)
    | x < y = x : sortedMerge xs (y:ys)
    | otherwise = y : sortedMerge (x:xs) ys

digitsToInt :: Num a => [a] -> a
digitsToInt [] = 0
digitsToInt xs = (last xs) + (10 * (digitsToInt $ init xs))

lTruncate :: Int -> Int
lTruncate n = digitsToInt $ tail $ digits $ fromIntegral n

rTruncate :: Int -> Int
rTruncate n = digitsToInt $ init $ digits $ fromIntegral n

isLTruncatablePrime :: Int -> Bool
isLTruncatablePrime n
    | n < 10 = isPrime n
    | otherwise = (isLTruncatablePrime $ lTruncate n) && isPrime n

isRTruncatablePrime :: Int -> Bool
isRTruncatablePrime n
    | n < 10 = isPrime n
    | otherwise = (isRTruncatablePrime $ rTruncate n) && isPrime n

isTruncatablePrime :: Int -> Bool
isTruncatablePrime n = isLTruncatablePrime n && isRTruncatablePrime n

truncatablePrimes = filter (\n -> isTruncatablePrime n && n > 10) primes

{- truncatablePrimeCandidates = concat-}
{-     [ x:([digitsToInt $ (digits x ++ [n]) | n <- [1,3,7,9] ]++[digitsToInt $ (n : digits x) | n <- [1,3,7,9] ]) | x <- truncatablePrimes]-}
