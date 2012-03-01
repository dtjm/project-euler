import Char

digits = concatMap show [0..]
indices = [1,10,100,1000,10000,100000,1000000]
total = product (map (\x -> digitToInt $ digits !! x) indices)
