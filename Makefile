CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g
LDFLAGS =  

SRC = test_set_int.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = proi_21l_201_lab4

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

main.o: set.h

test_set_int.o: set.h

clean:
	rm -rf $(OBJ) $(EXEC)