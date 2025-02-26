#include <SDL3/SDL.h>
#include <stdbool.h>
#include <context.h>
#include <border.h>

#ifndef APP_H
#define APP_H

typedef struct {
    const char* title;

    Context* ctx;
    
    Border* border;
    // topbar;

    SDL_Window* window;
    SDL_Renderer* renderer;
} App;

App* App_create(const char* title, int width, int height);
void App_destroy(App* app);

void App_setBorder(App* app, Border* border);

void App_run(App* app);

#endif