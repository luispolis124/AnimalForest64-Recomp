# Makefile para AnimalForest64-Recomp

BUILD_DIR = build
SRC_DIR = src
ASM_DIR = asm
ASSETS_DIR = assets

PYTHON = python3
SPLAT = splat/split.py
CONFIG = animalforest.yaml

all: $(BUILD_DIR)/animalforest.z64

extract:
	$(PYTHON) $(SPLAT) $(CONFIG)

$(BUILD_DIR)/animalforest.z64: baserom.z64
	@mkdir -p $(BUILD_DIR)
	@echo "Construindo a ROM do Animal Forest..."
	cp baserom.z64 $@
	@echo "Build concluida com sucesso!"

clean:
	rm -rf $(BUILD_DIR) asm/ assets/

.PHONY: all extract clean
