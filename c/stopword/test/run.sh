# This is just a quick and dirty script; there is undoubtedly a more elegant solution 

# Compile

gcc test_01.c ../stopword.c -Wall -Wextra -O3 -g -o test_01
gcc test_02.c ../stopword.c -Wall -Wextra -O3 -g -o test_02
gcc test_03.c ../stopword.c -Wall -Wextra -O3 -g -o test_03
gcc test_04.c ../stopword.c -Wall -Wextra -O3 -g -o test_04
gcc test_05.c ../stopword.c -Wall -Wextra -O3 -g -o test_05
gcc test_06.c ../stopword.c -Wall -Wextra -O3 -g -o test_06
gcc test_07.c ../stopword.c -Wall -Wextra -O3 -g -o test_07
gcc test_08.c ../stopword.c -Wall -Wextra -O3 -g -o test_08
gcc test_09.c ../stopword.c -Wall -Wextra -O3 -g -o test_09

# Run with valgrind

valgrind -q ./test_01
valgrind -q ./test_02
valgrind -q ./test_03
valgrind -q ./test_04
valgrind -q ./test_05
valgrind -q ./test_06
valgrind -q ./test_07
valgrind -q ./test_08
valgrind -q ./test_09

# Remove binaries

rm test_01 test_02 test_03 test_04 test_05 test_06 test_07 test_08 test_09