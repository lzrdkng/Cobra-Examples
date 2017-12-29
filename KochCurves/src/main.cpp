#include <iostream>

#include <time.h>
#include <stdlib.h>

#include <Cobra/Window.hpp>
#include <Cobra/Renderer.hpp>

#include "Koch.hpp"


void draw(SDL::Renderer& render, const std::vector<SDL::Point>& edges);


int main(int argc, char** argv)
{
  int side = 2;
	
  if (argc > 1) side = atoi(argv[1]);
  if (side < 2) side = 2;
	
  Koch koch(side, 200);

  SDL::init(SDL::InitVideo);

  SDL::Window window("Koch");
  window.setResizable(true);

  SDL::Renderer render(window, SDL::RendererAccelerated);



  SDL::Pair<int> size = window.getSize();

  render.setDrawColor(SDL::Color {0, 0, 0});
  render.clear();

  render.setDrawColor(SDL::Color {0xFF, 0xFF, 0xFF});

  render.drawLines(koch.getEdges(size.first, size.second));

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
      case SDLK_PERIOD:
	koch.increment();
	draw(render, koch.getEdges(size.first, size.second));
	break;
      case SDLK_COMMA:
	koch.decrement();
	draw(render, koch.getEdges(size.first, size.second));
	break;
      case SDLK_z:
	koch.zoomIn();
	draw(render, koch.getEdges(size.first, size.second));
	break;
      case SDLK_x:
	koch.zoomOut();
	draw(render, koch.getEdges(size.first, size.second));
	break;
      case SDLK_RIGHT:
	koch.move(1, 0);
	draw(render, koch.getEdges(size.first, size.second));
	break;
      case SDLK_LEFT:
	koch.move(-1, 0);
	draw(render, koch.getEdges(size.first, size.second));
	break;
      case SDLK_UP:
	koch.move(0, -1);
	draw(render, koch.getEdges(size.first, size.second));
	break;
      case SDLK_DOWN:
	koch.move(0, 1);
	draw(render, koch.getEdges(size.first, size.second));
	break;
      default:
	break;
      }

      continue;
    }
    else if (event.type == SDL_WINDOWEVENT)
      {
	switch (event.window.event)
	  {
	  case SDL_WINDOWEVENT_SIZE_CHANGED:
	  case SDL_WINDOWEVENT_RESIZED:
	    size = window.getSize();
	    draw(render, koch.getEdges(size.first, size.second));
	    break;
	  }

      }
 
  } while(true);

  SDL::quit();

  return 0;
}


void draw(SDL::Renderer& render, const std::vector<SDL::Point>& edges)
{
  render.setDrawColor(0);
  render.clear();
  
  render.setDrawColor(UINT32_MAX);

  for (uint i=0; i<edges.size(); i += 131071)
  {
    uint delta = i + 131071;

    if (delta > edges.size())
    {
      render.drawLines(std::vector<SDL::Point> {edges.begin() + i, edges.end()});
    }
    else
    {
      render.drawLines(std::vector<SDL::Point> {edges.begin() + i, edges.begin() + delta});
    }
      
  }

  render.present();
}
