import Data.List

perms :: (Eq a) => [a] -> [[a]]
perms [] = [[]]
perms xs = [ (a:b) | a <- xs, b <- perms (delete a xs) ]
