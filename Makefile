# Makefile para AnimalForest64 - Versão Nativa Linux / Termux

BUILD_DIR = build
PYTHON = python3
SPLAT = splat/split.py
CONFIG = animalforest.yaml
ELF = animalforest.elf

all:
	@echo "Executando o processo de recompilação e build..."
	$(PYTHON) $(SPLAT) $(CONFIG)
	@if [ ! -f "$(ELF)" ]; then \
		echo "ERRO: O arquivo $(ELF) não foi encontrado!"; \
		echo "Você precisa compilar a ROM para gerar o ELF antes de rodar o N64Recomp."; \
		exit 1; \
	fi
	./N64Recomp config.toml
	@echo "Recompilação realizada. Iniciando build nativo..."
	rm -rf $(BUILD_DIR)
	cmake -B $(BUILD_DIR) -S . -DCMAKE_BUILD_TYPE=Release
	cmake --build $(BUILD_DIR) -j$$(nproc)
	@echo "Build concluído com sucesso!"

extract:
	$(PYTHON) $(SPLAT) $(CONFIG)

recomp:
	./N64Recomp config.toml

clean:
	rm -rf $(BUILD_DIR) output_code RecompiledFuncs/*.c RecompiledFuncs/*.cpp

.PHONY: all extract recomp clean
