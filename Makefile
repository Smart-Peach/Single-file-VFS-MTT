.PHONY: clean, interpretor

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

all: interpretor clean 

interpretor:
	$(CXX) -c interpretor/Parser.cpp src/vfs_mtt_main.cpp interpretor/Interpretor.cpp $(SAN) $(STD)
	$(CXX) vfs_mtt_main.o Parser.o Interpretor.o -o main.out $(SAN) $(STD)
	rm *.o
	./main.out

test: 
	$(CXX) -c interpretor/Parser.cpp src/vfs_mtt_main.cpp interpretor/Interpretor.cpp $(STD)
	$(CXX) vfs_mtt_main.o Parser.o Interpretor.o -o main.out $(STD)
	rm *.o
	./main.out $(TEST_COMMANDS)

run-interpretor-gtest: 
	$(CXX) -c interpretor/Parser.cpp tests/interpretor_gtest.cpp interpretor/Interpretor.cpp $(SAN) $(STD)
	$(CXX) interpretor_gtest.o Parser.o Interpretor.o -o tests/test.out $(TEST_FLAGS) $(SAN) $(STD)
	rm *.o
	./tests/test.out

run-interpretor-test: 
	$(CXX) -c interpretor/Parser.cpp tests/interpretor_test.cpp interpretor/Interpretor.cpp $(STD)
	$(CXX) interpretor_test.o Parser.o Interpretor.o -o tests/test.out $(STD)
	rm *.o
	clear
	./tests/test.out

test-binary:
	$(CXX) tests/test_main_binary.cpp -o test_bin.out
	./test_bin.out
	rm *.out

clean: 
	rm *.out 