CXX      := g++
CXXSTD   := -std=c++17
WARN     := -Wall -Wextra -Wno-unused-parameter
OPT      := -O3
CXXFLAGS := $(CXXSTD) $(WARN) $(OPT) -MMD -MP -march=native -ffast-math

PPM2JPEG := ppmtojpeg

SRC_DIR     := src
INCLUDE_DIR := $(SRC_DIR)/include
BUILD_DIR   := build

MAIN       := $(SRC_DIR)/main.cpp
TARGET     := $(BUILD_DIR)/main
DEP        := $(BUILD_DIR)/main.d
RENDER_PPM := $(BUILD_DIR)/render.ppm
RENDER     := $(BUILD_DIR)/render.jpeg

.PHONY: all render debug clean

all: $(TARGET)
render: $(RENDER)

$(TARGET): $(MAIN) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $(MAIN) -o $@

$(RENDER): $(RENDER_PPM)
	$(PPM2JPEG) $< > $@

$(RENDER_PPM): $(TARGET)
	$(TARGET) > $@

$(BUILD_DIR):
	mkdir -p $@

debug: CXXFLAGS := $(CXXSTD) $(WARN) -O0 -g -fsanitize=address,undefined -MMD -MP
debug: clean $(TARGET)

clean:
	rm -rf $(BUILD_DIR)

-include $(DEP)
