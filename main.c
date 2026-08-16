#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Function prototypes for the system, recompiled game core, and RT64 engine
extern void N64_InitMemory(void);
extern void N64_LoadROM(const char* filepath);
extern void N64_RunOneFrame(void);
extern void N64_SetControllerButton(int button, bool pressed);
extern void RDP_Init(void);
extern void RDP_Shutdown(void);

// Basic mapping of PC keys to virtual Nintendo 64 controller buttons
static void HandleKeyboardInput(SDL_Keycode key, bool pressed) {
    switch (key) {
        case SDLK_x:      N64_SetControllerButton(0, pressed); break; // A Button
        case SDLK_c:      N64_SetControllerButton(1, pressed); break; // B Button
        case SDLK_RETURN: N64_SetControllerButton(3, pressed); break; // Start
        case SDLK_UP:     N64_SetControllerButton(4, pressed); break; // D-Pad Up
        case SDLK_DOWN:   N64_SetControllerButton(5, pressed); break; // D-Pad Down
        case SDLK_LEFT:   N64_SetControllerButton(6, pressed); break; // D-Pad Left
        case SDLK_RIGHT:  N64_SetControllerButton(7, pressed); break; // D-Pad Right
        case SDLK_z:      N64_SetControllerButton(8, pressed); break; // L Trigger
        case SDLK_a:      N64_SetControllerButton(9, pressed); break; // R Trigger
        case SDLK_SPACE:  N64_SetControllerButton(10, pressed); break; // Z Trigger
        default: break;
    }
}

int main(int argc, char* argv[]) {
    // 1. Initialize SDL2 subsystems (Video, Audio, and Joysticks)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0) {
        fprintf(stderr, "Failed to initialize SDL2: %s\n", SDL_GetError());
        return 1;
    }

    // Configure OpenGL context (compatible standard version)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    // 2. Create the native application window
    SDL_Window* window = SDL_CreateWindow(
        "Animal Forest Recompiled - Native Port (RT64)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        fprintf(stderr, "Failed to create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create the OpenGL rendering context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fprintf(stderr, "Failed to create OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_GL_SetSwapInterval(1); // Enable V-Sync

    // Initialize RT64 Graphics Subsystem Pipeline
    RDP_Init();

    // 3. Verify and validate ROM existence before starting the runtime (Flyingmeta style)
    const char* romPath = NULL;
    if (argc > 1) {
        FILE* f_arg = fopen(argv[1], "rb");
        if (f_arg) {
            fclose(f_arg);
            romPath = argv[1];
        }
    }

    if (!romPath) {
        // Try inside the build directory
        FILE* f_build = fopen("build/animalforest.z64", "rb");
        if (f_build) {
            fclose(f_build);
            romPath = "build/animalforest.z64";
        }
    }

    if (!romPath) {
        // Try in the root directory as baserom.z64
        FILE* f_base = fopen("baserom.z64", "rb");
        if (f_base) {
            fclose(f_base);
            romPath = "baserom.z64";
        }
    }

    // If no valid ROM was found, display a Flyingmeta-style warning and abort execution
    if (!romPath) {
        fprintf(stderr, "\n=================================================================\n");
        fprintf(stderr, "[CRITICAL ERROR] No valid ROM found for Animal Forest 64!\n");
        fprintf(stderr, "Please place 'baserom.z64' in the project root or in 'build/'.\n");
        fprintf(stderr, "=================================================================\n\n");
        
        // Display a native graphical error popup box
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Animal Forest 64 - Initialization Error",
            "ROM not found!\n\nPlease place the 'baserom.z64' file in the game directory to start.",
            window
        );

        RDP_Shutdown();
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 4. Initialize virtual memory and load the detected ROM
    printf("[Port Engine] Initializing N64 virtual memory...\n");
    N64_InitMemory();
    
    printf("[Port Engine] Loading ROM: %s\n", romPath);
    N64_LoadROM(romPath);

    // 5. Main Native Application Loop (with integrated debug logging)
    bool running = true;
    SDL_Event event;
    unsigned long long frame_count = 0;

    printf("[Port Engine] Starting main execution loop with RT64 pipeline...\n");
    while (running) {
        // Process window events, keyboard, and mouse inputs
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

        // Execute a complete frame of the recompiled game logic
        N64_RunOneFrame();

        // Frame debugging to track execution activity in the console
        frame_count++;
        if (frame_count % 60 == 0) {
            printf("[Debug] Frame %llu processed successfully via RT64 pipeline.\n", frame_count);
        }

        // Update the screen with rendered graphics
        SDL_GL_SwapWindow(window);
    }

    // 6. Clean shutdown of all resources
    printf("[Port Engine] Shutting down application...\n");
    RDP_Shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
