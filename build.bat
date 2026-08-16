@echo off
setlocal

echo [Build System] Iniciando a compilacao do Animal Forest Recompiled (.exe)...

:: Define o compilador MinGW para arquitetura de 64-bits
set CC=x86_64-w64-mingw32-gcc

:: Flags de otimizacao e inclusao de bibliotecas graficas e do SDL2
set CFLAGS=-O3 -Wall -mwindows
set LIBS=-lmingw32 -lSDL2main -lSDL2 -lopengl32 -lm

:: Arquivos fontes do projeto (Main + Código Recompilado + Camada de Runtime)
set SOURCES=main.c src/recompiled_game.c src/n64_runtime.c src/graphics_rdp.c

:: Executa a compilacao para gerar o executavel nativo do Windows
%CC% %SOURCES% -o AnimalForest.exe %CFLAGS% %LIBS%

if %ERRORLEVEL% EQU 0 (
    echo.
    echo [Sucesso!] O executavel AnimalForest.exe foi gerado com exito!
) else (
    echo.
    echo [Erro] Falha durante o processo de compilacao.
)

endlocal
pause
