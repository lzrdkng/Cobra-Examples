#include <SDLO/SDL.hpp>
#include <SDLO/Window.hpp>
#include <SDLO/Renderer.hpp>
#include <SDLO/Point.hpp>

#include "Mandelbrot.hpp"

int main()
{
  const  SDLO::Coord origin {0.3007597002215182, 0.0201501598261257};
  
  SDLO::init(SDLO::InitVideo);

  SDLO::Window window("Mandelbrot");

  SDLO::Renderer render(window, SDLO::RendererAccelerated);

  SDLO::Pair<int> size = window.getSize();

  Mandelbrot mandelbrot(origin, size.first, size.second, 1, 500);

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
	      
	  render.setDrawColor({128, 256, 64, color%256});
	  render.drawPoint(x, y);
	}
      }

      render.present();

      mandelbrot.zoomIn();

      if (mandelbrot.getZoom() >= 32768)
	quit = false;
      
    }
	
  } while(!quit);

  SDLO::quit();

  return 0;
}
