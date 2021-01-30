CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address -O3
LDFLAGS =  -fsanitize=address -O3

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
	$(CXX) -c -O3 $(CXX_FLAGS) $< -o $@


clean:
	rm -rf $(OBJ) $(EXEC)

.PHONY: run
run:
	make && ./build/dexter