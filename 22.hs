import Data.Char
import Data.List

charScore c = subtract 64 (ord (toUpper c))

stringScore cs = sum (map charScore cs)

readNames s = sort (words (map delimToSpace s))

scoreNames :: [[Char]] -> [(Int, Int)] -> [(Int, Int)]
scoreNames []     ps     = ps 
scoreNames (n:ns) []     = scoreNames ns [(1, stringScore n)]
scoreNames (n:ns) (p:ps) = scoreNames ns (nScore:p:ps)
			   where nScore = ((fst p) + 1, stringScore n)

processScore (r, s) = r * s

totalScore names = sum (map processScore (scoreNames names [])) 

delimToSpace c =
	case c of
		'"'  -> ' '
		','  -> ' '
		'\\' -> ' '
		_    -> c 

main = do 
	f <- readFile "names.txt"
	print (totalScore (readNames f))

names = ["ALLAN", "BETTY", "CHARLIE"]
