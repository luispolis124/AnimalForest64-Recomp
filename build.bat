@echo off
setlocal

echo [Build System] Iniciando a configuracao e compilacao do Animal Forest Recompiled via CMake...

:: Cria e entra no diretorio de build padrão
if not exist build mkdir build
cd build

:: Configura o projeto com CMake para 64-bits (Visual Studio ou MinGW padrão do sistema)
cmake .. -DCMAKE_BUILD_TYPE=Release

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [Erro] Falha na configuracao do CMake.
    goto error
)

:: Compila o projeto utilizando todos os núcleos disponíveis
cmake --build . --config Release

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [Erro] Falha durante o processo de compilacao.
    goto error
)

echo.
echo [Sucesso!] O projeto foi recompilado e compilado com exito na pasta build!
goto end

:error
echo.
echo [Falha] O processo de build foi interrompido devido a erros.

:end
cd ..
endlocal
pause
