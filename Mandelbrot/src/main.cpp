// std imports
#include <complex>
#include <iostream>
#include <iomanip>
// cobra imports
#include <Cobra/SDL.hpp>
#include <Cobra/Window.hpp>
// app import
#include "Mandelbrot.hpp"

typedef std::complex<long double> complex;

//const complex origin(0.3007597002215182, 0.0201501598261257);

const SDL::Coord origin(0, 0);

int main()
{
  SDL::init(SDL::InitVideo);

  SDL::Window root("Mandelbrot");

  Mandelbrot mandelbrot(root, origin, 2, 100);

  mandelbrot.renderImage();

  SDL_Event event;

  std::cout << std::setprecision(17);

  do
    {
      SDL_PollEvent(&event);

      if (event.type == SDL_QUIT)
        {
	  break;
        }
      else if (event.type == SDL_KEYDOWN)
        {
	  switch (event.key.keysym.sym)
            {
            case SDLK_DOWN:
	      break;
            case SDLK_UP:
	      break;
            case SDLK_LEFT:
	      break;
            case SDLK_RIGHT:
	      break;
            case SDLK_SPACE:
	      mandelbrot.zoomIn(2);
	      break;
            case SDLK_LSHIFT:
	      mandelbrot.zoomIn(0.5);
	      break;
            default:
	      break;
            }

	  std::cout << "Center: "
		    << mandelbrot.getCenter()
		    << "\nZoom: "
		    << mandelbrot.getZoom()
		    << "\nEpsilon: "
		    << mandelbrot.getEpsilon()
		    << "\n----------------------"
		    << std::endl;

	  mandelbrot.renderImage();

	  SDL_FlushEvent(SDL_KEYDOWN);
        }
    } while(true);

  SDL::quit();

  return 0;
}
