# Configuración del compilador
CXX := g++
CXXFLAGS := -Iinclude -Iinclude/commands -std=c++17 -pthread -Wall -Wextra -I/mingw64/include/SFML
LDFLAGS := -pthread -L/mingw64/lib
SFML_LIBS := -lsfml-audio -lsfml-system -lsfml-window -lsfml-graphics

# Directorios
SRC_DIR := src
SRC_COMMANDS_DIR := $(SRC_DIR)/commands
SRC_AUDIO_DIR := $(SRC_DIR)/audio
OBJ_DIR := obj

# Fuentes
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp) \
             $(wildcard $(SRC_COMMANDS_DIR)/*.cpp) \
             $(wildcard $(SRC_AUDIO_DIR)/*.cpp)
             
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cpp)) \
             $(patsubst $(SRC_COMMANDS_DIR)/%.cpp,$(OBJ_DIR)/commands/%.o,$(wildcard $(SRC_COMMANDS_DIR)/*.cpp)) \
             $(patsubst $(SRC_AUDIO_DIR)/%.cpp,$(OBJ_DIR)/audio/%.o,$(wildcard $(SRC_AUDIO_DIR)/*.cpp))

# Nombre del ejecutable
TARGET := Soonata.exe

# Regla principal
$(TARGET): $(OBJ_DIR)/main.o $(OBJ_FILES)
	$(CXX) $(LDFLAGS) $^ $(SFML_LIBS) -o $@

# Regla para main.cpp
$(OBJ_DIR)/main.o: main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para objetos principales
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para objetos de comandos
$(OBJ_DIR)/commands/%.o: $(SRC_COMMANDS_DIR)/%.cpp | $(OBJ_DIR)/commands
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para objetos de audio
$(OBJ_DIR)/audio/%.o: $(SRC_AUDIO_DIR)/%.cpp | $(OBJ_DIR)/audio
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorios necesarios
$(OBJ_DIR) $(OBJ_DIR)/commands $(OBJ_DIR)/audio:
	mkdir -p $@

# Copiar DLLs de SFML (renombrar quitando el prefijo 'lib')
copy_dlls:
	@echo "Copiando y renombrando DLLs de SFML..."
	cp /mingw64/bin/libsfml-audio-2.dll ./sfml-audio-2.dll
	cp /mingw64/bin/libsfml-system-2.dll ./sfml-system-2.dll
	cp /mingw64/bin/libsfml-window-2.dll ./sfml-window-2.dll
	cp /mingw64/bin/libsfml-graphics-2.dll ./sfml-graphics-2.dll
	@echo "DLLs copiadas y renombradas correctamente"

# Limpieza
clean:
	rm -rf $(OBJ_DIR) $(TARGET) sfml-*.dll

.PHONY: clean copy_dlls