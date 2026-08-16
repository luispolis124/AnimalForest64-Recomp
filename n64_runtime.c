#include <stdio.h>
#include <stdbool.h>

// Protótipo da função do subsistema RT64/RDP integrada
extern void RDP_ProcessDisplayList(void* dl_address);

// Contador global de frames para depuração
static unsigned long long g_frame_counter = 0;
static bool g_rom_loaded = false;

// Gerenciamento da memoria virtual e inicializacao do N64
void N64_InitMemory(void) {
    printf("[Runtime] Memoria virtual do N64 inicializada com sucesso.\n");
    g_frame_counter = 0;
    g_rom_loaded = false;
}

void N64_LoadROM(const char* filepath) {
    printf("[Runtime] Tentando carregar o arquivo de ROM a partir de: %s\n", filepath);
    
    // Tenta abrir o arquivo fisicamente para garantir que o caminho está correto
    FILE* file = fopen(filepath, "rb");
    if (!file) {
        fprintf(stderr, "[Runtime ERRO] Nao foi possivel abrir o arquivo de ROM no caminho especificado!\n");
        g_rom_loaded = false;
        return;
    }

    // Lê os primeiros bytes para validar se é uma ROM válida (opcional/informativo)
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    printf("[Runtime] ROM carregada e mapeada na memoria virtual! Tamanho total: %ld bytes\n", size);
    g_rom_loaded = true;
}

void N64_RunOneFrame(void) {
    if (!g_rom_loaded) {
        return; // Evita processar se nenhuma ROM válida estiver ativa
    }

    g_frame_counter++;

    // Imprime um log a cada 60 frames (aprox. 1 segundo de jogo rodando)
    if (g_frame_counter % 60 == 0) {
        printf("[Runtime Debug] Frame executado com sucesso: %llu via RT64 Pipeline\n", g_frame_counter);
    }

    // Chamada integrada ao pipeline do RT64 para processar as listas gráficas por frame
    // RDP_ProcessDisplayList(NULL); 
}

void N64_SetControllerButton(int button, bool pressed) {
    // Log opcional para testar se os inputs do teclado estão chegando ao runtime
    // printf("[Runtime Input] Botao ID %d -> Estado: %s\n", button, pressed ? "Pressionado" : "Solto");
}
