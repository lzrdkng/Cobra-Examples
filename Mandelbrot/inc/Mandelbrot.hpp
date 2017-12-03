#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include <Cobra/SDL.hpp>

class Mandelbrot
{

public:

  constexpr explicit Mandelbrot(const SDL::Coord& ORIGIN,
				int WIDTH,
				int HEIGHT,
				double ZOOM,
				unsigned MAX)
    : origin {ORIGIN}, width {WIDTH}, height {HEIGHT}, zoom {ZOOM}, max {MAX} {}
    

  constexpr double getZoom() const { return zoom; }

  constexpr const SDL::Coord& getOrigin() const { return origin; }

  constexpr double getWidth() const { return width; }

  constexpr double getHeight() const { return height; }
  
  Mandelbrot& zoomIn()
  {
    zoom *= 2;
    return *this;
  }

  Mandelbrot& zoomOut()
  {
    zoom /= 2;
    return *this;
  }

  Mandelbrot& moveFrom(const SDL::Coord& coord)
  {
    origin += coord;
    return *this;
  }

  Mandelbrot& moveTo(const SDL::Coord& coord)
  {
    origin = coord;
    return *this;
  }


  uint iterate(const SDL::Point& coord) const
  {
    SDL::Coord z = SDL::screenToCartesian(coord,
					  width,
					  height,
					  zoom,
					  origin);
    SDL::Coord c {z};

    uint i = 0;
    
    while (std::abs(z) < 2 && i < max)
    {
      z = z*z + c;
      ++i;
    }
    
    if (std::abs(z) > 2)
      return 0;

    return i;
  }

private:

  double zoom;

  SDL::Coord origin;

  int width;

  int height;

  uint max;

};  


#endif // MANDELBROT_HPP
