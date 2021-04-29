CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -g -fsanitize=address
LDFLAGS =  -fsanitize=address

SRC = entity.cpp invoice.cpp product.cpp receipt.cpp units.cpp item.cpp main.cpp cash_register.cpp cash_worker.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = proi_21l_201_projekt

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

invoice.o: invoice.h receipt.h contractor.h

product.o: product.h entity.h units.h

receipt.o: receipt.h product.h entity.h

item.o: item.h product.h units.h

cash_worker.o: cash_worker.h cash_register.h buyer.h

cash_register.o: cash_register.h cash_worker.h invoice.h buyer.h

main.o: item.h receipt.h

clean:
	rm -rf $(OBJ) $(EXEC)