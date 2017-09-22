COMPILER = gcc
COMPILER_FLAGS = -Wall -Wmissing-braces

TARGET_NAME := aes
TARGET_DIR := bin
TARGET_PATH := $(TARGET_DIR)/$(TARGET_NAME)

BUILD_DIR := build

SRC_DIR := src
SRC_EXTENSION := c
SOURCES := $(filter-out $(SRC_DIR)/main.$(SRC_EXTENSION), $(shell find $(SRC_DIR) -name '*.$(SRC_EXTENSION)'))
OBJECTS := $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, $(SOURCES:.$(SRC_EXTENSION)=.o))

all: AES

AES: $(TARGET_PATH)

clean:
	@echo "cleaning";
	$(RM) -r $(BUILD_DIR) $(TARGET_DIR)

.PHONY: all

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXTENSION)
	@mkdir -p $(dir $@)
	@echo "building" $@
	@$(COMPILER) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) -c -o $@ $<

$(TARGET_PATH): $(OBJECTS) $(BUILD_DIR)/main.o
	@echo "linking $(TARGET_PATH)"
	@mkdir -p $(TARGET_DIR)
	@echo $(COMPILER) $@
	@$(COMPILER) $(COMPILER_FLAGS) $^ -o $@
	@echo
