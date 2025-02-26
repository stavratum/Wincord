#include <SDL3/SDL.h>
#include <border.h>

Border* Border_create(Context* parent, int size) {
    Border* border = SDL_malloc(sizeof(Border));
    border->size   = size;
    border->parent = parent;
    border->rects  = SDL_malloc( sizeof( SDL_FRect[size] ) );
    
    Border_updateSize(border);

    return border;
}

void Border_destroy(Border* border) {
    SDL_free(border->rects);
    SDL_free(border);
}

SDL_HitTestResult Border_hitTest(SDL_Window* window, const SDL_Point* point, void* data) {
    Border* border = (Border*)(data);

    int size = border->size + 2;
    int w = border->parent->width;
    int h = border->parent->height;
    
    int x = point->x;
    int y = point->y;

    if (x < size && y < size) {
        return SDL_HITTEST_RESIZE_TOPLEFT;
    } else if (x > size && x < w - size && y < size) {
        return SDL_HITTEST_RESIZE_TOP;
    } else if (x > w - size && y < size) {
        return SDL_HITTEST_RESIZE_TOPRIGHT;
    } else if (x > w - size && y > size && y < h - size) {
        return SDL_HITTEST_RESIZE_RIGHT;
    } else if (x > w - size && y > h - size) {
        return SDL_HITTEST_RESIZE_BOTTOMRIGHT;
    } else if (x < w - size && x > size && y > h - size) {
        return SDL_HITTEST_RESIZE_BOTTOM;
    } else if (x < size && y > h - size) {
        return SDL_HITTEST_RESIZE_BOTTOMLEFT;
    } else if (x < size && y < h - size && y > size) {
        return SDL_HITTEST_RESIZE_LEFT;
    }

    return SDL_HITTEST_NORMAL;
}

int Border_update(Border* border, SDL_Event* event)
{
    switch (event->type) {
        case SDL_EVENT_WINDOW_RESIZED: Border_updateSize(border);
        case SDL_EVENT_QUIT:           Border_destroy   (border);
    }

    //if (event->type == SDL_EVENT_WINDOW_RESIZED) { Border_updateSize(border); }
    //if (event->type == SDL_EVENT_QUIT)           { Border_destroy   (border); }
}

void Border_updateSize(Border* border)
{
    for (int size = 0; border->size > size; size++) {
        struct SDL_FRect rect = {
            .x = size,
            .y = size,
            .w = border->parent->width  - (size * 2),
            .h = border->parent->height - (size * 2),
        };

        border->rects[size] = rect;
    }
}

void Border_render(Border* border, SDL_Renderer* r ) {
    SDL_SetRenderDrawColor(r, 152, 154, 158, 255);
    SDL_RenderRects(r, border->rects, border->size);
}