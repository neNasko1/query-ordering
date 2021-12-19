for((i = 1; ; i ++)); do
    ./gen 0 > inputs/testInput.in
    ./main 1 < inputs/testInput.in 
    ./main 2 < inputs/testInput.in
done
