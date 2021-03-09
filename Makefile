CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address -O0
LDFLAGS =  -fsanitize=address -O0

SRCDIR = ./src
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR = ./obj
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.cpp=.o)))
EXEC = build/dexter

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/*.h
	@mkdir -p ./build
	@mkdir -p ./obj
	@rm -f ./build/dexter
	$(CXX) -c -O3 $(CXX_FLAGS) $< -o $@

doc: 
	doxygen Doxyfile

clean:
	rm -rf $(OBJ) $(EXEC)

.PHONY: run
run:
	make -j8 && ./build/dexter