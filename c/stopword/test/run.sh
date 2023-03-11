# Compile and run tests with valgrind

for i in {1..11}
do
    gcc test_$(printf "%02d" $i).c ../stopword.c -Wall -Wextra -fanalyzer -O3 -g -o test_$i
    valgrind -q ./test_$i
    rm test_$i
done