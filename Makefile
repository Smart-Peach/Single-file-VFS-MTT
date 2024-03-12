.PHONY: clean, interpretor

CXX = clang++

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
	$(CXX) -c interpretor/Parser.cpp src/vfs_mtt_main.cpp interpretor/Interpretor.cpp $(SAN)
	$(CXX) vfs_mtt_main.o Parser.o Interpretor.o -o main.out $(SAN)
	rm *.o
	./main.out

test: 
	$(CXX) -c interpretor/Parser.cpp src/vfs_mtt_main.cpp interpretor/Interpretor.cpp 
	$(CXX) vfs_mtt_main.o Parser.o Interpretor.o -o main.out
	rm *.o
	./main.out $(TEST_COMMANDS)

run-interpretor-gtest: 
	$(CXX) -c interpretor/Parser.cpp tests/interpretor_gtest.cpp interpretor/Interpretor.cpp $(SAN)
	$(CXX) interpretor_gtest.o Parser.o Interpretor.o -o tests/test.out $(TEST_FLAGS) $(SAN) 
	rm *.o
	./tests/test.out

run-interpretor-test: 
	$(CXX) -c interpretor/Parser.cpp tests/interpretor_test.cpp interpretor/Interpretor.cpp
	$(CXX) interpretor_test.o Parser.o Interpretor.o -o tests/test.out
	rm *.o
	clear
	./tests/test.out

clean: 
	rm *.o 