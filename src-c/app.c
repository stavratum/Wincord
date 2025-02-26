#include <SDL3/SDL.h>
#include <app.h>

App* App_create(const char* title, int width, int height)
{
    if (!SDL_Init   (SDL_INIT_VIDEO            )) return false;
    if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1")) return false;
        
    SDL_Window* window = SDL_CreateWindow(title, width, height,
        SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN
    );
    if (!window) return 0;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0);
    if (!renderer) return 0;    
    else
    {
        SDL_SetRenderVSync(renderer, 1);
    }

    App* app         = SDL_malloc(sizeof(App));
    app->title       = title;

    app->ctx         = SDL_malloc(sizeof(Context));
    app->ctx->width  = width;
    app->ctx->height = height;

    app->window      = window;
    app->renderer    = renderer;
        
    return app;
}

void App_destroy(App* app)
{
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);

    SDL_free(app->ctx);
    SDL_free(app);

    SDL_Quit();
}

void App_setBorder(App* app, Border* border) {
    app->border = border;
    SDL_SetWindowHitTest(app->window, &Border_hitTest, (void*)border);
}

void App_run(App* app)
{
    SDL_ShowWindow(app->window);
    SDL_Event event;

    goto L_Draw;
    
    while (1) {
        if (SDL_WaitEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    Border_update(app->border, &event);
                    return;
                case SDL_EVENT_WINDOW_RESIZED:
                    app->ctx->width  = event.window.data1;
                    app->ctx->height = event.window.data2;
            }

            Border_update(app->border, &event);
        }

    L_Draw:
        SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
        SDL_RenderClear(app->renderer);
        
        Border_render(app->border, app->renderer);
        
        SDL_RenderPresent(app->renderer);
        SDL_Delay(0);
    }
}