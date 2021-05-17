CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g -fsanitize=address -Wno-unknown-pragmas -Wno-pmf-conversions
LDFLAGS = -fsanitize=address

SRC_SHOP = entity.cpp invoice.cpp product.cpp receipt.cpp units.cpp item.cpp cash_register.cpp cash_worker.cpp person.cpp worker.cpp customer.cpp shop.cpp
SRC = $(SRC_SHOP:%=shop/%) main.cpp simulation.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = proi_21l_201_projekt

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

shop/invoice.o: shop/invoice.h shop/receipt.h shop/contractor.h

shop/product.o: shop/product.h shop/entity.h shop/units.h

shop/receipt.o: shop/receipt.h shop/product.h shop/entity.h shop/cash_register.h

shop/item.o: shop/item.h shop/product.h shop/units.h

shop/cash_worker.o: shop/cash_worker.h shop/cash_register.h shop/buyer.h

shop/cash_register.o: shop/cash_register.h shop/cash_worker.h shop/invoice.h shop/buyer.h shop/shop.h

shop/person.o: shop/person.h shop/contractor.h shop/entity.h

shop/worker.o: shop/worker.h shop/cash_worker.h shop/cash_register.h shop/entity.h shop/shop.h

shop/customer.o: shop/customer.h shop/person.h shop/product.h shop/buyer.h shop/shop.h shop/cash_register.h

shop/shop.o: shop/shop.h shop/contractor.h shop/item.h shop/worker.h shop/customer.h

simulation.o: simulation.h shop/shop.h

main.o: shop/item.h shop/receipt.h

clean:
	rm -rf $(OBJ) $(EXEC)