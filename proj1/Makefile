CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SCANNER_BIN_NAME = scanner
RECOGNIZER_BIN_NAME = recognizer

recognizer: recognizer.cpp lexer.o
	$(CXX) $(CXXFLAGS) -o $(RECOGNIZER_BIN_NAME) types.o lexeme.o lexer.o recognizer.cpp

scanner: scanner.cpp lexer.o
	$(CXX) $(CXXFLAGS) -o $(SCANNER_BIN_NAME) types.o lexeme.o lexer.o scanner.cpp

tests: test1 test2 test3 test4 test5

debug: debug1 debug2 debug3 debug4 debug5

test1: recognizer
	-./recognizer tests/test1.in

test2: recognizer
	-./recognizer tests/test2.in

test3: recognizer
	-./recognizer tests/test3.in

test4: recognizer
	-./recognizer tests/test4.in

test5: recognizer
	-./recognizer tests/test5.in

debug1: recognizer
	-./recognizer tests/test1.in d

debug2: recognizer
	-./recognizer tests/test2.in d

debug3: recognizer
	-./recognizer tests/test3.in d

debug4: recognizer
	-./recognizer tests/test4.in d

debug5: recognizer
	-./recognizer tests/test5.in d

run: recognizer
	@echo "Use make tests or make test1, make test2, etc. to get the output of each test."
	@ if ./recognizer tests/test1.in 2>&1 | cmp -s - tests/test1.out;\
	then \
	 	echo "Test 1 passed";\
	else \
		echo "Test 1 failed! Run make test1 to get the output.";\
	fi
	@ if ./recognizer tests/test2.in 2>&1 | cmp -s - tests/test2.out;\
	then \
	 	echo "Test 2 passed";\
	else \
		echo "Test 2 failed! Run make test2 to get the output.";\
	fi
	@ if ./recognizer tests/test3.in 2>&1 | cmp -s - tests/test3.out;\
	then \
	 	echo "Test 3 passed";\
	else \
		echo "Test 3 failed! Run make test3 to get the output.";\
	fi
	@ if ./recognizer tests/test4.in 2>&1 | cmp -s - tests/test4.out;\
	then \
	 	echo "Test 4 passed";\
	else \
		echo "Test 4 failed! Run make test4 to get the output.";\
	fi
	@ if ./recognizer tests/test5.in 2>&1 | cmp -s - tests/test5.out;\
	then \
	 	echo "Test 5 passed";\
	else \
		echo "Test 5 failed! Run make test5 to get the output.";\
	fi

scannertests: scannertest1 scannertest2 scannertest3 scannertest4 scannertest5

scannertest1: scanner
	-./scanner tests/scanner/test1.in

scannertest2: scanner
	-./scanner tests/scanner/test2.in

scannertest3: scanner
	-./scanner tests/scanner/test3.in

scannertest4: scanner
	-./scanner tests/scanner/test4.in

scannertest5: scanner
	-./scanner tests/scanner/test5.in

testscanner: scanner
	@echo "Use make tests or make scannertest1, make scannertest2, etc. to get the output of each test."
	@ if ./scanner tests/scanner/test1.in 2>&1 | cmp -s - tests/scanner/test1.out;\
	then \
	 	echo "Test 1 passed";\
	else \
		echo "Test 1 failed! Run make scannertest1 to get the output.";\
	fi
	@ if ./scanner tests/scanner/test2.in 2>&1 | cmp -s - tests/scanner/test2.out;\
	then \
	 	echo "Test 2 passed";\
	else \
		echo "Test 2 failed! Run make scannertest2 to get the output.";\
	fi
	@ if ./scanner tests/scanner/test3.in 2>&1 | cmp -s - tests/scanner/test3.out;\
	then \
	 	echo "Test 3 passed";\
	else \
		echo "Test 3 failed! Run make scannertest3 to get the output.";\
	fi
	@ if ./scanner tests/scanner/test4.in 2>&1 | cmp -s - tests/scanner/test4.out;\
	then \
	 	echo "Test 4 passed";\
	else \
		echo "Test 4 failed! Run make scannertest4 to get the output.";\
	fi
	@ if ./scanner tests/scanner/test5.in 2>&1 | cmp -s - tests/scanner/test5.out;\
	then \
	 	echo "Test 5 passed";\
	else \
		echo "Test 5 failed! Run make scannertest5 to get the output.";\
	fi



types.o: types.cpp types.hpp
	$(CXX) $(CXXFLAGS) -c types.cpp

lexeme.o: lexeme.cpp lexeme.hpp types.o
	$(CXX) $(CXXFLAGS) -c lexeme.cpp

lexer.o: lexer.cpp lexer.hpp lexeme.o
	$(CXX) $(CXXFLAGS) -c lexer.cpp



clean:
	rm -f *.o $(SCANNER_BIN_NAME) $(RECOGNIZER_BIN_NAME)
