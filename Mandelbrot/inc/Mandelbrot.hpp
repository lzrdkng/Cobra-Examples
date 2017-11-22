#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

// std import
#include <complex>
// cobra imports
#include <Cobra/SDL.hpp>
#include <Cobra/Point.hpp>
#include <Cobra/Window.hpp>
#include <Cobra/Renderer.hpp>


typedef std::complex<long double> complex;

class Mandelbrot
{

public:

  explicit Mandelbrot(SDL::Window& window,
                      const SDL::Coord& origin,
                      double zoom,
                      unsigned maxIteration);

  virtual ~Mandelbrot();


  long double getZoom() const;

  long double getEpsilon() const;

  complex getCenter() const;

  double getWidth() const;

  double getHeight() const;

  Mandelbrot& renderImage();
  
  Mandelbrot& zoomIn(long double factor);

  Mandelbrot& moveFrom(complex c);

  Mandelbrot& moveTo(complex c);

protected:

  long double iterate(complex c) const;

  Mandelbrot& renderPixel(unsigned x, unsigned y, long double color);


private:

  SDL::Renderer m_renderer;

  SDL_PixelFormat* m_format;

  long double m_zoom;
 
  SDL::Coord m_center;

  double m_width;

  double m_height;

  unsigned m_maxIteration;

};


#endif // MANDELBROT_HPP
