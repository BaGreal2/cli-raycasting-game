CXX = g++
CXXFLAGS = -O3 -ffunction-sections -fdata-sections -flto -march=native -std=c++20 -lncurses
SRC = src/main.cpp src/graphics.cpp src/shapes.cpp
OUT = build

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
