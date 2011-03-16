module Main where
import Data.Set

terms = (toList . fromList) $ 
		[ a^b | a <- [2..100], b <- [2..100] ]

main = do print $ length terms
