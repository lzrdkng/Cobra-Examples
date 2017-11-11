#include "Koch.hpp"

#include <Cobra/Window.hpp>
#include <Cobra/Renderer.hpp>
#include <time.h>
#include <stdlib.h>

int main()
{
    Koch koch(5, 200);

    SDL::init(SDL::InitVideo);

    SDL::Window window("Koch", 500, 500);

    SDL::Renderer render(window, SDL::RendererAccelerated);

    render.setDrawColor(SDL::Color {0, 0, 0});
    render.clear();

    render.setDrawColor(SDL::Color {0xFF, 0xFF, 0xFF});

    render.drawLines(koch.getEdges());

    render.present();

    SDL_Event event;

    srand(time(NULL));

    do
    {
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            break;
        }
        else if(event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                koch.iterate();
                render.setDrawColor(SDL::Color {0x00, 0x00, 0x00});
                render.clear();

                std::vector<SDL::Pair<SDL::Point>> edges = koch.getEdges();
                for (auto it = edges.begin(); it!= edges.end(); ++it)
                {
                    render.setDrawColor(SDL::Color {rand()%UINT32_MAX});
                    render.drawLine(*it);
                }

                render.present();
                break;

            }

            SDL_FlushEvent(SDL_KEYDOWN);
        }

    } while(true);

    SDL::quit();

    return 0;
}
