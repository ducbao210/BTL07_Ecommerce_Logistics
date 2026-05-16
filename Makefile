CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC_DIR = src
OBJ_DIR = obj
TARGET = logistics_app

# File nguồn chính
MAIN_SRC = main.cpp
MAIN_OBJ = $(OBJ_DIR)/main.o

# Các file nguồn trong thư mục src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Toàn bộ object files
ALL_OBJECTS = $(MAIN_OBJ) $(OBJECTS)

# Mục tiêu mặc định
all: $(TARGET)

# Link executable
$(TARGET): $(ALL_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile main.cpp
$(MAIN_OBJ): $(MAIN_SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile src/*.cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Tạo thư mục obj và output (tương thích Windows)
$(OBJ_DIR):
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	if not exist output mkdir output

# Dọn dẹp
clean:
	if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	if exist $(TARGET).exe del /q $(TARGET).exe
	if exist $(TARGET) del /q $(TARGET)
	if exist output rmdir /s /q output

.PHONY: all clean