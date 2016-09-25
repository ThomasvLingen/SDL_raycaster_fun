#include "Game.h"

Game::Game() {
    if(!init()) {
        printf("Couldn't create the game\n");
    } else {
        run();
    }
}

Game::~Game() {
    cleanup();
}

void Game::addObject(GameObject* toAdd) {
    this->objects.push_back(toAdd);
}

bool Game::init() {
    // Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING < 0)) {
        printf("Something went wrong while initting: %s\n", SDL_GetError());
        return false;
    }

    // Init SDL_TTF
    if (TTF_Init() < 0) {
        printf("Something went wrong while initting SDL_TTF!%s\n", TTF_GetError());
    };

    // Init window
    printf("initting window\n");
    if (!this->init_window()) {
        return false;
    }

    printf("initting renderer\n");
    if (!this->init_renderer()) {
        return false;
    }

    printf("initting done\n");
    return true;
}

bool Game::init_window()
{
    window = SDL_CreateWindow("Vidya gaem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window != NULL) {
        screenSurface = SDL_GetWindowSurface(window);
        return true;
    } else {
        printf("Something went wrong while making a window! : %s\n", SDL_GetError());
        return false;
    }
}

bool Game::init_renderer()
{
    // Attempt to make a software renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);
    if (this->renderer != NULL) {
        printf("Warning: could not use hardware acceleration --> SDL_Renderer uses software rendering\n");
        return true;
    } else {
        printf("Something went wrong while making a renderer! : %s\n", SDL_GetError());
        return false;
    }
}

void Game::run() {
    int timeSinceLastFrame;
    int lastFrameStartTime = SDL_GetTicks();
    int frameStartTime;
    int timeSpent;

    Player* player = new Player(this->renderer);

    this->addObject(player);
    this->addObject(new RaycasterWorld(this->renderer, player));
    this->fps = new FPSCounter(this->renderer);

    while(running) {
        frameStartTime = SDL_GetTicks();
        timeSinceLastFrame = frameStartTime - lastFrameStartTime;
        lastFrameStartTime = SDL_GetTicks();

        update(timeSinceLastFrame);

        draw();

        timeSpent = frameStartTime - SDL_GetTicks();
        SDL_Delay((1000 / 60) - timeSpent);
    }
}

void Game::handleInput(SDL_Event* event) {
    switch(event->type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            keyboard.keyPressed(event->key.keysym.sym);
            break;
        case SDL_KEYUP:
            keyboard.keyReleased(event->key.keysym.sym);
            break;
        default:
            break;
    }
}

void Game::update(int timeSinceLastUpdate) {
    SDL_Event event;

    while(SDL_PollEvent(&event) != 0) {
        handleInput(&event);
    }

    if(keyboard.isDown(SDLK_ESCAPE)) {
        running = false;
    }

    // Have all GameObjects do their thing with the given input
    for(GameObject* obj : this->objects) {
        (*obj).handleInput(this->keyboard);
    }
    this->fps->handleInput(this->keyboard);

    // Have all GameObjects update
    for(GameObject* obj : this->objects) {
        (*obj).update(timeSinceLastUpdate);
    }
    this->fps->update(timeSinceLastUpdate);
}

void Game::draw() {
    // Draw background
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

    // Have all GameObjects draw themselves
    for(GameObject* obj : this->objects) {
        (*obj).draw(screenSurface);
    }

    this->fps->draw(screenSurface);

    // Update window surface
    SDL_UpdateWindowSurface(window);
}

void Game::cleanup() {
    SDL_DestroyWindow(window);

    SDL_Quit();
}
