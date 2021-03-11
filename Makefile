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
	$(CXX) -O3 -o $@ $(OBJ) $(LBLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/*.h
	@mkdir -p ./build
	@mkdir -p ./obj
	@rm -f ./build/dexter
	$(CXX) -c -Wall -Werror -Wextra -pedantic -std=c++17 -O3 $< -o $@

doc: 
	doxygen Doxyfile

clean:
	rm -rf $(OBJ) $(EXEC)

.PHONY: run
run:
	make -j8 && ./build/dexter
