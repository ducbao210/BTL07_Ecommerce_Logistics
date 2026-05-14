CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC_DIR = src
OBJ_DIR = obj
TARGET = logistics_app

# main.cpp nằm ở thư mục gốc
MAIN_SRC = main.cpp
MAIN_OBJ = $(OBJ_DIR)/main.o

# Các file .cpp trong thư mục src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Danh sách toàn bộ object files
ALL_OBJECTS = $(MAIN_OBJ) $(OBJECTS)

all: $(TARGET)

# Tạo executable
$(TARGET): $(ALL_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Biên dịch main.cpp
$(MAIN_OBJ): $(MAIN_SRC) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Biên dịch các file trong src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Tạo thư mục obj và output (Windows)
$(OBJ_DIR):
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	if not exist output mkdir output

# Xóa file build (Windows)
clean:
	if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	if exist $(TARGET).exe del /q $(TARGET).exe
	if exist $(TARGET) del /q $(TARGET)
	if exist output\* del /q output\*

.PHONY: all clean