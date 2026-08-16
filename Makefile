# Makefile para AnimalForest64 - Versão Nativa com RT64 (.exe / Recomp)

BUILD_DIR = build
ASM_DIR = asm
ASSETS_DIR = assets

# Compiladores separados para C e C++ para evitar conflitos de stdbool.h com a STL
CC = x86_64-w64-mingw32-gcc
CXX = x86_64-w64-mingw32-g++

# Flags para arquivos C
CFLAGS = -O2 -Wall -mwindows -Iinclude -D__STDC_WANT_LIB_EXT1__=1 -D_MM_MALLOC_H_INCLUDED

# Flags para arquivos C++ (RT64)
CXXFLAGS = -O2 -Wall -std=c++17 -mwindows -Iinclude -Irt64/include -D__STDC_WANT_LIB_EXT1__=1 -D_MM_MALLOC_H_INCLUDED

# Adicionadas bibliotecas do RT64 (Direct3D 12 / Vulkan, dxgi, d3dcompiler) além do SDL2 e OpenGL
LIBS = -Llib -lmingw32 -lSDL2main -lSDL2 -lopengl32 -ld3d12 -ldxgi -ld3dcompiler -limm32 -lversion -lole32 -luuid -lm -lshell32 -luser32 -lkernel32

# Separação dos arquivos fontes por linguagem
C_FILES = main.c n64_runtime.c graphics_rdp.c chkstk.c
CPP_FILES = rt64/rt64_integration.cpp

# Objetos gerados
OBJS = $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o)

PYTHON = python3
SPLAT = splat/split.py
CONFIG = animalforest.yaml

all: AnimalForest.exe

# Regra para extrair a ROM original usando o Splat
extract:
	$(PYTHON) $(SPLAT) $(CONFIG)

# Regra de compilação para arquivos C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de compilação para arquivos C++
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra de linkagem para gerar o executável nativo do Windows com RT64
AnimalForest.exe: $(OBJS)
	@echo "Linkando o AnimalForest.exe com motor gráfico RT64..."
	$(CXX) $(OBJS) -o $@ $(LIBS)
	@echo "Build com RT64 concluida com sucesso!"

# Regra para empacotar tudo no ZIP oficial de releases
release: AnimalForest.exe
	@echo "Criando o pacote AnimalForest64.zip com suporte RT64..."
	mkdir -p release_package
	cp AnimalForest.exe release_package/
	# Tenta copiar a SDL2.dll do ambiente do MinGW se disponível
	cp /usr/x86_64-w64-mingw32/bin/SDL2.dll release_package/ 2>/dev/null || \
	cp /data/data/com.termux/files/usr/opt/llvm-mingw-w64/x86_64-w64-mingw32/bin/SDL2.dll release_package/ 2>/dev/null || true
	@echo -e "Animal Forest 64 - Recompiled Port (RT64 Engine)\n\nControles:\nX = A | C = B | ENTER = Start | Setas = D-Pad" > release_package/README.txt
	cd release_package && zip -r ../AnimalForest64.zip *
	rm -rf release_package
	@echo "Pacote AnimalForest64.zip gerado com sucesso para as Releases!"

# Limpeza dos arquivos gerados
clean:
	rm -rf $(BUILD_DIR) $(OBJS) AnimalForest.exe AnimalForest64.zip release_package

.PHONY: all extract release clean
