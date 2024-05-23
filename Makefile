CXX := clang++
CXXFLAGS := -fno-exceptions -Werror -Wall -fno-omit-frame-pointer -Wstring-conversion -DNDEBUG -fprofile-instr-generate -fcoverage-mapping -fsanitize=address -g

all: fuzzer

fuzzer: fuzzer.o message.pb.o
	$(CXX) $(CXXFLAGS) -fsanitize=fuzzer -o fuzzer \
        -Wl,-rpath,/usr/local/lib fuzzer.o message.pb.o \
        -L/usr/local/lib -lprotobuf-mutator-libfuzzer -lprotobuf-mutator -lprotobuf -pthread

fuzzer.o: message.pb.h
	$(CXX) $(CXXFLAGS) -fsanitize=fuzzer-no-link -std=gnu++11 \
        -I/usr/local/include/libprotobuf-mutator -I. \
        -c main.cc -o fuzzer.o

message.pb.o: message.pb.cc
	$(CXX) $(CXXFLAGS) -fsanitize-coverage=0 -std=gnu++11 -fno-coverage-mapping \
	-I. \
	-c message.pb.cc

message.pb.h message.pb.cc:
	protoc --cpp_out=. message.proto

run: fuzzer
	./fuzzer -runs=500000

coverage: fuzzer
	./fuzzer -runs=50000
	llvm-profdata merge -sparse default.profraw -o default.profdata
	llvm-cov show ./fuzzer  -instr-profile=default.profdata


.PHONY: clean
clean:
	rm fuzzer default.* *.o *.pb.*
