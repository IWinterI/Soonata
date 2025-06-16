# Configuración del compilador
CXX := g++
CXXFLAGS := -Iinclude -Iinclude/commands -std=c++17 -pthread -Wall -Wextra
LDFLAGS := -pthread

# Directorios
SRC_DIR := src
SRC_COMMANDS_DIR := $(SRC_DIR)/commands
OBJ_DIR := obj

# Fuentes
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_COMMANDS_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cpp)) \
              $(patsubst $(SRC_COMMANDS_DIR)/%.cpp,$(OBJ_DIR)/commands/%.o,$(wildcard $(SRC_COMMANDS_DIR)/*.cpp))

# Nombre del ejecutable
TARGET := Soonata.exe

# Regla principal
$(TARGET): $(OBJ_DIR)/main.o $(OBJ_FILES)
	$(CXX) $(LDFLAGS) $^ -o $@

# Regla para main.cpp
$(OBJ_DIR)/main.o: main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para objetos principales
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para objetos de comandos
$(OBJ_DIR)/commands/%.o: $(SRC_COMMANDS_DIR)/%.cpp | $(OBJ_DIR)/commands
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorios necesarios
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/commands:
	mkdir -p $(OBJ_DIR)/commands

# Limpieza
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: clean