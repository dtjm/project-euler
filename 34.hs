fac :: Int -> Int
fac 0 = 1
fac n = fac(n-1) * n

-- Converts a String into a list of Strings of 1 char each
charStrings :: String -> [String]
charStrings xs = [ [x] | x <- xs]

-- Converts an String to an integer
readInt :: String -> Int
readInt = read

-- converts a number to a list of digits
digits :: Int -> [Int]
digits n = map readInt ( charStrings ( show n ) )

-- get the curious sum (the sum of the factorial of each integer in the list)
curiousSum :: Int -> Int
curiousSum n = sum ( map fac ( digits n ) )

numberEqualToCuriousSum :: Int -> Bool
numberEqualToCuriousSum n = curiousSum n == n

main :: IO()
main = do
    putStrLn "Calculating..."
    putStrLn $ show $ take 2 [ x | x <- [3..100000000], numberEqualToCuriousSum x ]


-- Project Euler solution
-- http://projecteuler.net/thread=34
{- sum ([x | x <- [1..100000], x == sum (map (\n -> product [1..n]) (map (digitToInt) (show x)))])-}
