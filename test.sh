for((i = 1; ; i ++)); do
    ./dist/gen 0 > inputs/testInput.in
    ./dist/main 1 < inputs/testInput.in 
    ./dist/main 2 < inputs/testInput.in
done
