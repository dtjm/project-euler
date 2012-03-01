import PELib
import Data.List

isPandigital :: Int -> Bool
isPandigital n = (sort $ digits n) == [1..len]
    where len = length $ show n
