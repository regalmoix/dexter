CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -O0
LDFLAGS =-O0 -g

SRCDIR = ./src
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR = ./obj
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.cpp=.o)))
EXEC = build/dexter

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -O3 -march=native -g -o $@ $(OBJ) $(LBLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/*.h
	@mkdir -p ./build
	@mkdir -p ./obj
	@rm -f ./build/dexter
	$(CXX) -c -march=native -Wall -Werror -Wno-char-subscripts -Wextra -pedantic -g -std=c++17 -O3 $< -o $@

doc: 
	doxygen Doxyfile

clean:
	rm -rf $(OBJ) $(EXEC)

rebuild:
	make clean && make -j8

.PHONY: run
run:
	make -j8 && ./build/dexter
