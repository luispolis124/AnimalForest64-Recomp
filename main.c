#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

// Protótipos das funções do sistema e do núcleo recompilado do jogo
extern void N64_InitMemory(void);
extern void N64_LoadROM(const char* filepath);
extern void N64_RunOneFrame(void);
extern void N64_SetControllerButton(int button, bool pressed);

// Mapeamento básico de teclas do PC para botões virtuais do Nintendo 64
static void HandleKeyboardInput(SDL_Keycode key, bool pressed) {
    switch (key) {
        case SDLK_x:      N64_SetControllerButton(0, pressed); break; // Botão A
        case SDLK_c:      N64_SetControllerButton(1, pressed); break; // Botão B
        case SDLK_RETURN: N64_SetControllerButton(3, pressed); break; // Start
        case SDLK_UP:     N64_SetControllerButton(4, pressed); break; // Direcional Cima
        case SDLK_DOWN:   N64_SetControllerButton(5, pressed); break; // Direcional Baixo
        case SDLK_LEFT:   N64_SetControllerButton(6, pressed); break; // Direcional Esquerda
        case SDLK_RIGHT:  N64_SetControllerButton(7, pressed); break; // Direcional Direita
        case SDLK_z:      N64_SetControllerButton(8, pressed); break; // Gatilho L
        case SDLK_a:      N64_SetControllerButton(9, pressed); break; // Gatilho R
        case SDLK_SPACE:  N64_SetControllerButton(10, pressed); break; // Z Trigger
        default: break;
    }
}

int main(int argc, char* argv[]) {
    // 1. Inicializa o subsistema do SDL2 (Vídeo, Áudio e Controles)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0) {
        fprintf(stderr, "Erro ao inicializar o SDL2: %s\n", SDL_GetError());
        return 1;
    }

    // Configura o contexto OpenGL (versão padrão compatível)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    // 2. Cria a janela nativa do executável
    SDL_Window* window = SDL_CreateWindow(
        "Animal Forest Recompiled - Native Port",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        fprintf(stderr, "Erro ao criar a janela do SDL: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Cria o contexto de renderização OpenGL
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "Erro ao criar o contexto OpenGL: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_GL_SetSwapInterval(1); // Ativa V-Sync

    // 3. Inicializa a memória virtual e carrega a ROM base
    printf("[Port Engine] Inicializando a memoria virtual do N64...\n");
    N64_InitMemory();
    
    // Tenta carregar a ROM se passada por argumento, ou usa o padrão
    const char* romPath = (argc > 1) ? argv[1] : "animal_forest.z64";
    printf("[Port Engine] Carregando ROM: %s\n", romPath);
    N64_LoadROM(romPath);

    // 4. O Loop Principal do Aplicativo Nativo
    bool running = true;
    SDL_Event event;

    printf("[Port Engine] Iniciando o loop principal de execucao...\n");
    while (running) {
        // Processa eventos da janela e do teclado/mouse
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    HandleKeyboardInput(event.key.keysym.sym, true);
                    break;
                case SDL_KEYUP:
                    HandleKeyboardInput(event.key.keysym.sym, false);
                    break;
                default:
                    break;
            }
        }

        // Executa um frame completo da lógica recompilada do jogo
        N64_RunOneFrame();

        // Atualiza a tela com os gráficos renderizados
        SDL_GL_SwapWindow(window);
    }

    // 5. Encerramento limpo dos recursos
    printf("[Port Engine] Encerrando aplicacao...\n");
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
