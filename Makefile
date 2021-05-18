CXX = g++
CXXFLAGS += -march=native -Wall -Werror -Wno-char-subscripts -Wextra -pedantic -std=c++2a -O3 -DNDEBUG -g
LDFLAGS += -O3 -march=native -DNDEBUG -g

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
	$(CXX) -c $(CXXFLAGS) $< -o $@

doc: 
	doxygen Doxyfile

clean:
	rm -rf $(OBJ) $(EXEC)

rebuild:
	make clean && make -j8

.PHONY: run
run:
	@make -j8 && ./build/dexter
