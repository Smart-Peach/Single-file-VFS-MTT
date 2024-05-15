.PHONY: clean, interpreter

CXX := clang++
STD := -std=c++20

ASAN := -fsanitize=address
UBSAN := -fsanitize=undefined
SAN := -fsanitize=undefined,address
TEST_FLAGS := -lgtest -lgmock -pthread



ifeq (test,$(firstword $(MAKECMDGOALS)))
  TEST_COMMANDS :=  $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(TEST_COMMANDS):;@:)
endif

all: interpreter clean 


gen-bin-file:
	$(CXX) -c tests/generate_file.cpp $(SAN) $(STD)
	$(CXX) generate_file.o -o test.out $(TEST_FLAGS) $(SAN) $(STD)
	./test.out
	rm *.out

interpreter:
	$(CXX) -c src/interpreter/Lexer.cpp src/interpreter/Parser.cpp src/structures/AwesomeFileSystem.cpp src/structures/Superblock.cpp src/structures/Inode.cpp src/structures/InodeMap.cpp src/interpreter/Interpreter.cpp  src/vfs_mtt_main.cpp $(STD)
	$(CXX) vfs_mtt_main.o Lexer.o Superblock.o Inode.o InodeMap.o Parser.o AwesomeFileSystem.o Interpreter.o -o main.out $(STD)
	rm *.o
	./main.out

interpreter-san:
	$(CXX) -c src/interpreter/Parser.cpp src/interpreter/Interpreter.cpp src/vfs_mtt_main.cpp $(SAN) $(STD)
	$(CXX) vfs_mtt_main.o Parser.o Interpreter.o -o main.out $(TEST_FLAGS) $(SAN) $(STD)
	rm *.o
	./main.out

test-interpreter: 
	$(CXX) -c src/interpreter/Lexer.cpp src/interpreter/Parser.cpp  tests/test_interpreter.cpp src/structures/AwesomeFileSystem.cpp src/structures/Superblock.cpp src/structures/Inode.cpp src/structures/InodeMap.cpp src/interpreter/Interpreter.cpp $(SAN) $(STD)
	$(CXX) test_interpreter.o Lexer.o Superblock.o Inode.o InodeMap.o Parser.o AwesomeFileSystem.o Interpreter.o -o tests/test.out $(TEST_FLAGS) $(SAN) $(STD)
	./tests/test.out
	rm *.o 


test-hash-function:
	$(CXX) tests/test_hash_function.cpp -o test_bin.out $(STD)
	./test_bin.out
	rm *.out


test-binary:
	$(CXX) -c src/interpreter/Lexer.cpp src/interpreter/Parser.cpp  tests/test_main_binary.cpp src/structures/AwesomeFileSystem.cpp src/structures/Superblock.cpp src/structures/Inode.cpp src/structures/InodeMap.cpp src/interpreter/Interpreter.cpp $(STD)
	$(CXX) test_main_binary.o Lexer.o Superblock.o Inode.o InodeMap.o Parser.o AwesomeFileSystem.o Interpreter.o -o test.out $(STD)
	./test.out
	rm *.out *.o

test-superblock:
	$(CXX) tests/test_superblock_func.cpp src/structures/Superblock.cpp src/structures/Inode.cpp src/structures/InodeMap.cpp src/structures/AwesomeFileSystem.cpp -o test_bin.out
	./test_bin.out
	rm *.out

test-seek:
	$(CXX) tests/test_seekg.cpp -o test_seek.out $(STD)
	./test_seek.out
	rm *.out

clean: 
	rm *.out 