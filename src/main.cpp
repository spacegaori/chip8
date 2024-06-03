// #include <print>
#include <SDL2/SDL.h>

struct sdl_t
{
    SDL_Window* window;
    SDL_Renderer* renderer;
};

struct config_t
{
    uint32_t window_width;
    uint32_t window_height;
    uint32_t fg_color;
    uint32_t bg_color;
    uint32_t scale_factor;
};

enum class emulator_state_t
{
    QUIT,
    RUNNING,
    PAUSED,
};

struct chip8_t
{
    emulator_state_t state;
};

bool setConfig(config_t& config, const int argc, char **argv)
{
    config = config_t{
        .window_width = 64,     // X Resolution
        .window_height = 32,    // Y Resolution
        .fg_color = 0xFFFFFFFF, // foreground color
        .bg_color = 0xFFFF00FF, // background color
        .scale_factor = 20,
    };

    for (int i = 0; i < argc; i++)
    {
        (void)argv[i];
    }

    return true;
}

bool initSdl(sdl_t& sdl, const config_t& config)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER != 0))
    {
        SDL_Log("Could not initialize SDL subsystems! %s\n", SDL_GetError());
        return false;
    }

    sdl.window = SDL_CreateWindow(
        "CHIP-8",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        config.window_width * config.scale_factor,
        config.window_height * config.scale_factor,
        0
    );

    if (!sdl.window)
    {
        SDL_Log("Could not create SDL window %s\n", SDL_GetError());
        return false;
    }

    sdl.renderer = SDL_CreateRenderer(
        sdl.window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!sdl.renderer)
    {
        SDL_Log("Could not create SDL renderer %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool initChip8(chip8_t& chip8)
{
    chip8.state = emulator_state_t::RUNNING;
    return true;
}

void cleanUp(const sdl_t& sdl)
{
    SDL_DestroyRenderer(sdl.renderer);
    SDL_DestroyWindow(sdl.window);
    SDL_Quit();
}

void clearScreen(const sdl_t& sdl, const config_t& config)
{
    // const uint8_t r = (config.bg_color >> 24 ) & 0xFF;
    const uint8_t r{ static_cast<uint8_t>(config.bg_color >> 24 ) };
    const uint8_t g{ static_cast<uint8_t>(config.bg_color >> 16 ) };
    const uint8_t b{ static_cast<uint8_t>(config.bg_color >> 8 ) };
    const uint8_t a{ static_cast<uint8_t>(config.bg_color >> 0 ) };
    SDL_SetRenderDrawColor(sdl.renderer, r, g, b, a);
    SDL_RenderClear(sdl.renderer);
}

void updateScreen(const sdl_t& sdl)
{
    SDL_RenderPresent(sdl.renderer);
}

void handleInput(chip8_t& chip8)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            chip8.state = emulator_state_t::QUIT;
            return;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                chip8.state = emulator_state_t::QUIT;
                return;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            break;
        default:
            break;
        }
        // Handle events
    }
}

int main(int argc, char** argv) {
    // Initialize emulator configuration & options
    config_t config{};
    if (!setConfig(config, argc, argv))
    {
        exit(EXIT_FAILURE);
    }

    // Initialize SDL
    sdl_t sdl{};
    if (!initSdl(sdl, config))
    {
        exit(EXIT_FAILURE);
    }

    // Initialize CHIP-8
    chip8_t chip8{};
    if (!initChip8(chip8))
    {
        exit(EXIT_FAILURE);
    }

    // Initial screen clear to background color
    clearScreen(sdl, config);

    // Main Loop
    while (chip8.state != emulator_state_t::QUIT)
    {
        handleInput(chip8);

        if (chip8.state == emulator_state_t::PAUSED)
        {
            continue;
        }

        // Emulate CHIP-8 instructions

        // Delay for 60hz/fps
        SDL_Delay(16);
        clearScreen(sdl, config);
        updateScreen(sdl);
    }

    cleanUp(sdl);

    return 0;
}