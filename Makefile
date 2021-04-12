CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = application.cpp contractor.cpp invoice.cpp item.cpp main.cpp units.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = proi_21l_201_lab3

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

application.o: invoice.h

invoice.o: contractor.h item.h

item.o: units.h

clean:
	rm -rf $(OBJ) $(EXEC)