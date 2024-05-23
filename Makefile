fuzzer: DNP3.cc DNP3.h main.cc
	clang++  -DNDEBUG -fprofile-instr-generate -fcoverage-mapping  -g -fsanitize=fuzzer  main.cc  -o fuzzer

run: fuzzer
	./fuzzer -runs=500000

coverage: fuzzer
	./fuzzer -runs=500000
	llvm-profdata merge -sparse default.profraw -o default.profdata
	llvm-cov show ./fuzzer  -instr-profile=default.profdata


.PHONY: clean
clean:
	rm fuzzer
