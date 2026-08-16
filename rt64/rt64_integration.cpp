#include <stdio.h>

extern "C" {
    void RDP_Init(void);
    void RDP_ProcessDisplayList(void* dl_address);
    void RDP_Shutdown(void);
}

// Implementação da ponte de integração C++ para o RT64 Engine
extern "C" void RT64_InitPipeline(void) {
    printf("[RT64 Integration] Inicializando hooks de renderização avançada...\n");
    RDP_Init();
}

extern "C" void RT64_ExecuteCommand(void* dl_address) {
    RDP_ProcessDisplayList(dl_address);
}

extern "C" void RT64_ClosePipeline(void) {
    printf("[RT64 Integration] Fechando pipeline gráfico...\n");
    RDP_Shutdown();
}
