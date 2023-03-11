# Compile and run tests with valgrind

for i in {1..10}
do
    gcc test_$(printf "%02d" $i).c ../eval.c ../../pir-code/pir.c ../../stopword/stopword.c ../../stem/stem.c ../../string-util/string-util.c -Wall -Wextra -fanalyzer -O3 -g -o test_$i
    valgrind -q ./test_$i
    rm test_$i
done