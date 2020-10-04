min3 a b c = min a (min b c)

match a b 
    | a == b  = 0
    | a /= b  = 1

lev_rec s1 s2 = _lev_rec s1 (length s1) s2 (length s2)

_lev_rec s1 i s2 j
    | i == 0 = j
    | j == 0 = i
    | otherwise = min3 
        ((+)  (_lev_rec s1  (i-1) s2 (j-1) ) ( match (s1 !! (i-1)) (s2 !! (j-1))))
        ((+1) (_lev_rec s1  (i-1) s2  j  ) )
        ((+1) (_lev_rec s1   i    s2 (j-1)))

main = do  
    putStrLn "input s1: "  
    s1 <- getLine  
    
    putStrLn "input s2: "  
    s2 <- getLine 

    putStrLn ("dis lev: " ++  show (lev_rec s1 s2))