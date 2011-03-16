import Data.List

rDiv (x:[]) y = [(x `div` y)]
rDiv (x:xs) y = (x `div` y) : rDiv ((10*(x `mod` y) + head xs) : tail xs) y

reciprocal n = rDiv (1:[0,0..]) n

containsSublist _ [] = True
containsSublist [] _ = False
containsSublist list@(x:xs) sublist = list `startsWith` sublist || xs `containsSublist` sublist

doesntContainSublist xs ys = not (containsSublist xs ys)

startsWith []     _	 = False
startsWith _	  [] 	 = True
startsWith (x:[]) (y:[]) = x == y
startsWith (x:xs) (y:ys) = x == y && startsWith xs ys

doesntStartWith xs ys = not (startsWith xs ys)

isRepeating list pattern
	| length list < 2 * (length pattern) = False
	| otherwise = repeatsNTimes list pattern ((length list) `div` (length pattern))

repeatsNTimes list pattern 0 = True
repeatsNTimes list pattern n = list `startsWith` pattern && repeatsNTimes (drop (length pattern) list) pattern (n-1)

repeats (x:xs) = repeat' xs [x]

repeat' list@(x:xs) []	       = repeat' xs [x]
repeat' list@(x:xs) pat@(p:ps) 
	| isRepeating list pat = pat
	| list `doesntStartWith` pat && list `containsSublist` pat = repeat' xs (pat ++ [x])
	| list `doesntStartWith` pat && list `doesntContainSublist` pat = repeat' list (tail pat) 
	| list `startsWith` pat	&& list `containsSublist` pat = repeat' xs (pat ++ [x]) 
	| otherwise = []

reciprocalRepeatLength n = length $ repeats $ take 10000 $ reciprocal n

--candidates = filter f5 $ filter f3 $ filter f2 [1..999]
--	where 	f2 = (/=0) . (`mod` 2)
--	 	f3 = (/=0) . (`mod` 3)
--		f5 = (/=0) . (`mod` 5)

candidates = [1..9999]

results = zip (map reciprocalRepeatLength candidates) candidates

main = do print $ results
	  print $ snd $ maximum results
--solution = maximum results
--	where compare a b = compare (snd a) (snd b)

