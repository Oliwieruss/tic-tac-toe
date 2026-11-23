CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
SRC      = $(wildcard src/*.cpp)
OBJ      = $(SRC:.cpp=.o)
TARGET   = tictactoe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
