import PELib
import Data.Char
import Numeric

intToBinaryString :: Int -> [Char]
intToBinaryString n = showIntAtBase 2 intToDigit n ""

isBiPalindromic :: Int -> Bool
isBiPalindromic n = (isPalindrome $ digits $ fromIntegral n) && (isPalindrome $ intToBinaryString n)

bipalindromics = filter isBiPalindromic [1,3..]
