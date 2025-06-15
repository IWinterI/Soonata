SRC_DIR := src
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,%.o,$(SRC_FILES))

CXX := g++
CXXFLAGS := -Iinclude -std=c++17 -pthread -Wall -Wextra
LDFLAGS := -pthread

Soonata.exe: $(OBJ_FILES) main.o
	$(CXX) $(LDFLAGS) $^ -o $@  

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@  

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@  

clean:
	del /q *.o Soonata.exe