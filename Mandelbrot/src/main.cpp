#include <Cobra/SDL.hpp>
#include <Cobra/Window.hpp>
#include <Cobra/Renderer.hpp>
#include <Cobra/Point.hpp>

#include "Mandelbrot.hpp"

int main()
{
  const  SDL::Coord origin {0.3007597002215182, 0.0201501598261257};
  
  SDL::init(SDL::InitVideo);

  SDL::Window window("Mandelbrot");

  SDL::Renderer render(window, SDL::RendererAccelerated);

  SDL::Pair<int> size = window.getSize();

  Mandelbrot mandelbrot(origin, size.first, size.second, 1, 100);

  SDL_Event event;

  bool quit = false;

  do
  {
      
    while (SDL_PollEvent(&event) != 0)
      if (event.type == SDL_QUIT)
	quit = true;

    if (!quit)
    {
      render.setDrawColor(0);
      render.clear();
	  
      for (int x=0; x<size.first; ++x)
      {
	for (int y=0; y<size.second; ++y)
	{
	  uint color = mandelbrot.iterate({x, y});
	      
	  render.setDrawColor({color, color, color});
	  render.drawPoint(x, y);
	}
      }

      render.present();

      mandelbrot.zoomIn();

      if (mandelbrot.getZoom() >= 32768)
	quit = false;
      
    }
	
  } while(!quit);

  SDL::quit();

  return 0;
}
