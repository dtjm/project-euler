-- ProjectEuler/31.hs
import Data.List
import PELib

coins :: [Int]
coins = [1,2,5,10,20,50,100,200]

c :: Int -> [[Integer]]
c = 
	let c' 0 = [[]]
	    c' n = nub $ concat $ [ map (sort . (x:)) (c (n-x)) | x <- validCoins ]
		where validCoins = filter (<=n) coins
	in (map c' [0 ..] !!)

lc = length . c

doins = tail coins

d :: Int -> [Int] -> Int
d n xs 
	| n < 0 = 0
	| n == 0 = 1
	| otherwise = 1 + sum [ d (n-x) (filter (<=x) xs) | x <- xs ]

main = do print $ d 200 doins
