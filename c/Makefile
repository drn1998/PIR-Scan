pir-scan: main.o dir-iterator.o eval.o pir.o stem.o stopword.o string-util.o
	gcc -o pir-scan main.o dir-iterator.o eval.o pir.o stem.o stopword.o string-util.o -g

main.o: main.c
	gcc -c main.c -march=native -O3 -g

dir-iterator.o: dir-iterator/dir-iterator.c
	gcc -c dir-iterator/dir-iterator.c -march=native -O3 -g

eval.o: eval/eval.c
	gcc -c eval/eval.c -march=native -O3 -g

pir.o: pir-code/pir.c
	gcc -c pir-code/pir.c -march=native -O3 -g

stem.o: stem/stem.c
	gcc -c stem/stem.c -march=native -O3 -g

stopword.o: stopword/stopword.c
	gcc -c stopword/stopword.c -march=native -O3 -g

string-util.o: string-util/string-util.c
	gcc -c string-util/string-util.c -march=native -O3 -g

clean:
	rm main.o dir-iterator.o eval.o pir.o stem.o stopword.o string-util.o