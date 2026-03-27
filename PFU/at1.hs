main :: IO ()
main = do
    a <- readLn
    b <- readLn
    c <- readLn
    putStrLn $ heron a b c


ehTriangulo a b c
    | a>b+c = False
    | b>a+c = False
    | c>a+b = False
    | otherwise = True
heron a b c
    | ehTriangulo a b c = show area
    | otherwise = "-"
    where
        s = (a+b+c)/2
        area = sqrt(s*(s-a)*(s-b)*(s-c))