#include <stdio.h>

// Definicao manual de booleano para evitar erros de inclusao cruzada
typedef int bool;
#define true 1
#define false 0

// Gerenciamento da memoria virtual e inicializacao do N64
void N64_InitMemory(void) {
    printf("[Runtime] Memoria virtual do N64 inicializada.\n");
}

void N64_LoadROM(const char* filepath) {
    printf("[Runtime] Carregando arquivo de ROM: %s\n", filepath);
}

void N64_RunOneFrame(void) {
    // Execucao de um frame do nucleo recompilado
}

void N64_SetControllerButton(int button, bool pressed) {
    // Mapeamento de entrada dos botoes do controle
}
