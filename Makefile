.PHONY: clean, interpretor

CXX = clang++

ASAN := -fsanitize=address
UBSAN := -fsanitize=undefined
SAN := -fsanitize=undefined,address
TEST_FLAGS := -lgtest -lgmock -pthread

ifeq (test,$(firstword $(MAKECMDGOALS)))
  TEST_COMMAND := $(word 2, $(MAKECMDGOALS))
  $(eval $(TEST_COMMAND):;@:)
endif

all: interpretor clean 

interpretor:
	$(CXX) -c interpretor/Parser.cpp src/vfs_mtt_main.cpp interpretor/Interpretor.cpp $(SAN)
	$(CXX) vfs_mtt_main.o Parser.o Interpretor.o -o main.out $(SAN)
	./main.out

test: 
	$(CXX) -c interpretor/Parser.cpp src/vfs_mtt_main.cpp interpretor/Interpretor.cpp 
	$(CXX) vfs_mtt_main.o Parser.o Interpretor.o -o main.out
	rm *.o
	./main.out $(TEST_COMMAND)
	

clean: 
	rm *.o 