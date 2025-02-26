#include <SDL3/SDL.h>
#include <context.h>

#ifndef BORDER_H
#define BORDER_H

typedef struct {
    int size;

    Context* parent; 
    SDL_FRect* rects;
} Border;

Border* Border_create(Context* parent, int size);
void Border_destroy(Border* border);

SDL_HitTestResult Border_hitTest(SDL_Window* window, const SDL_Point* point, void* border);

int Border_update(Border* border, SDL_Event* ev);
void Border_updateSize(Border* border);

void Border_render(Border* border, SDL_Renderer* r);

#endif