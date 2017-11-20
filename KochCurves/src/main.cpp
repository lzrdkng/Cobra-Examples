#include "Koch.hpp"

#include <Cobra/Window.hpp>
#include <Cobra/Renderer.hpp>
#include <time.h>
#include <stdlib.h>


void draw(SDL::Renderer& render, const std::vector<SDL::Pair<SDL::Point>>& edges);


int main(int argc, char** argv)
{
  int side = 2;
	
  if (argc > 1) side = atoi(argv[1]);
  if (side < 2) side = 2;
	
  Koch koch(side, 200);

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
	koch.increment();
	draw(render, koch.getEdges());
	break;
      case SDLK_LSHIFT:
	koch.decrement();
	draw(render, koch.getEdges());
	break;
      }

      SDL_FlushEvent(SDL_KEYDOWN);
    }

  } while(true);

  SDL::quit();

  return 0;
}


void draw(SDL::Renderer& render, const std::vector<SDL::Pair<SDL::Point>>& edges)
{
  render.setDrawColor(0);
  render.clear();
  
  for (auto it = edges.begin(); it != edges.end(); ++it)
  {
    render.setDrawColor(rand()%UINT32_MAX);
    render.drawLine(*it);
  }

  render.present();
}
