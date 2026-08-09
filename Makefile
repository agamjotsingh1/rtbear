CXX = g++
CXXFLAGS = -O2 -std=c++17
PPM2JPEG = ppmtojpeg

SRC_DIR = src
MAIN = $(SRC_DIR)/main.cpp
INCLUDE_DIR = src/include
BUILD_DIR = build
TARGET = $(BUILD_DIR)/main
RENDER_PPM = $(BUILD_DIR)/render.ppm
RENDER = $(BUILD_DIR)/render.jpeg

all: $(RENDER)

$(RENDER): $(RENDER_PPM)
	$(PPM2JPEG) $(RENDER_PPM) > $(RENDER) 

$(RENDER_PPM): $(TARGET)
	$(TARGET) > $(RENDER_PPM) 

$(TARGET): $(MAIN) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(MAIN) -o $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
