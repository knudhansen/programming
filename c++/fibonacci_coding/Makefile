all: fib_decoding fib_coding 32bit_coding

clean:
	rm fib_coding fib_decoding 32bit_coding

compile=g++ -g

fib_decoding: fibonacci_decoding.cpp
	$(compile) fibonacci_decoding.cpp -o fib_decoding

fib_coding: fibonacci_coding.cpp
	$(compile) fibonacci_coding.cpp -o fib_coding

32bit_coding: 32bit_coding.cpp
	$(compile) 32bit_coding.cpp -o 32bit_coding
