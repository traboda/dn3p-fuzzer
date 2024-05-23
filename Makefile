fuzzer: DNP3.cc DNP3.h main.cc
	clang++ -fsanitize=fuzzer -DNDEBUG  main.cc  -o fuzzer

run: fuzzer
	./fuzzer -runs=500000

.PHONY: clean
clean:
	rm fuzzer
