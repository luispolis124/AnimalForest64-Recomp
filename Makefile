# Makefile para AnimalForest64 - Versão Nativa (.exe / Recomp)

BUILD_DIR = build
ASM_DIR = asm
ASSETS_DIR = assets

# Compilador cruzado do MinGW para Windows (gerando .exe no Linux/Termux)
CC = x86_64-w64-mingw32-gcc

# Flags padrão sem o nodefaultlibs, mantendo os contornos de include
CFLAGS = -O2 -Wall -mwindows -Iinclude -D__STDC_WANT_LIB_EXT1__=1 -D_MM_MALLOC_H_INCLUDED
# Adicionadas as bibliotecas do Windows necessárias (-lshell32 para o SDL2main)
LIBS = -Llib -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lm -lshell32 -luser32 -lkernel32

# Fontes C do projeto (incluindo o nosso main.c, a camada de runtime/jogo e o stub do chkstk)
SRC_FILES = main.c n64_runtime.c graphics_rdp.c chkstk.c

PYTHON = python3
SPLAT = splat/split.py
CONFIG = animalforest.yaml

all: AnimalForest.exe

# Regra para extrair a ROM original usando o Splat
extract:
	$(PYTHON) $(SPLAT) $(CONFIG)

# Regra de compilação cruzada para gerar o executável nativo do Windows
AnimalForest.exe: $(SRC_FILES)
	@echo "Compilando o AnimalForest.exe nativo..."
	$(CC) $(SRC_FILES) -o $@ $(CFLAGS) $(LIBS)
	@echo "Build concluida com sucesso!"

# Regra para empacotar tudo no ZIP oficial de releases
release: AnimalForest.exe
	@echo "Criando o pacote AnimalForest64.zip..."
	mkdir -p release_package
	cp AnimalForest.exe release_package/
	# Tenta copiar a SDL2.dll do ambiente do MinGW se disponível
	cp /usr/x86_64-w64-mingw32/bin/SDL2.dll release_package/ 2>/dev/null || \
	cp /data/data/com.termux/files/usr/opt/llvm-mingw-w64/x86_64-w64-mingw32/bin/SDL2.dll release_package/ 2>/dev/null || true
	@echo -e "Animal Forest 64 - Recompiled Port\n\nControles:\nX = A | C = B | ENTER = Start | Setas = D-Pad" > release_package/README.txt
	cd release_package && zip -r ../AnimalForest64.zip *
	rm -rf release_package
	@echo "Pacote AnimalForest64.zip gerado com sucesso para as Releases!"

# Limpeza dos arquivos gerados
clean:
	rm -rf $(BUILD_DIR) AnimalForest.exe AnimalForest64.zip release_package

.PHONY: all extract release clean
