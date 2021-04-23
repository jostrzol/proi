CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g
LDFLAGS =  

SRC = test_set_int.cpp test_set_int_pair.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = proi_21l_201_lab4

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

main.o: test_set_int.o test_set_int.o

test_set_int.o: test_set_int.h set.h

test_set_int_pair.o: test_set_int_pair.h set.h

clean:
	rm -rf $(OBJ) $(EXEC)