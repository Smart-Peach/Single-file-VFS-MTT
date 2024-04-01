.PHONY: clean, interpreter

CXX = clang++
STD = -std=c++20

ASAN := -fsanitize=address
UBSAN := -fsanitize=undefined
SAN := -fsanitize=undefined,address
TEST_FLAGS := -lgtest -lgmock -pthread

ifeq (test,$(firstword $(MAKECMDGOALS)))
  TEST_COMMANDS :=  $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(TEST_COMMANDS):;@:)
endif

all: interpreter clean 

interpreter:
	$(CXX) -c interpreter/Parser.cpp src/vfs_mtt_main.cpp interpreter/Interpreter.cpp $(SAN) $(STD)
	$(CXX) vfs_mtt_main.o Parser.o Interpreter.o -o main.out $(SAN) $(STD)
	rm *.o
	./main.out

test: 
	$(CXX) -c interpreter/Parser.cpp src/vfs_mtt_main.cpp interpreter/Interpreter.cpp $(STD)
	$(CXX) vfs_mtt_main.o Parser.o Interpreter.o -o main.out $(STD)
	rm *.o
	./main.out $(TEST_COMMANDS)

run-interpreter-gtest: 
	$(CXX) -c interpreter/Parser.cpp tests/interpreter_gtest.cpp interpreter/Interpreter.cpp $(SAN) $(STD)
	$(CXX) interpreter_gtest.o Parser.o Interpreter.o -o tests/test.out $(TEST_FLAGS) $(SAN) $(STD)
	rm *.o
	./tests/test.out

run-interpreter-test: 
	$(CXX) -c interpreter/Parser.cpp tests/interpreter_test.cpp interpreter/Interpreter.cpp $(STD)
	$(CXX) interpreter_test.o Parser.o Interpreter.o -o tests/test.out $(STD)
	rm *.o
	clear
	./tests/test.out

test-binary:
	$(CXX) tests/test_main_binary.cpp -o test_bin.out
	./test_bin.out
	rm *.out

clean: 
	rm *.out 