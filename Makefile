CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = set.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = proi_21l_201_lab4

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

main.o: set.h

set.o: set.h

clean:
	rm -rf $(OBJ) $(EXEC)