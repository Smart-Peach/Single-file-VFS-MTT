.PHONY: clean, interpretor

CXX = clang++

ASAN := -fsanitize=address
UBSAN := -fsanitize=undefined
SAN := -fsanitize=undefined,address
TEST_FLAGS := -lgtest -lgmock -pthread

all: interpretor clean 

interpretor:
	$(CXX) -c interpretor/Parser.cpp src/vfs_mtt_main.cpp $(SAN)
	$(CXX) vfs_mtt_main.o Parser.o $(SAN) -o main.out 
	./main.out

clean: 
	rm *.o *.out