#ifndef KOCH_HPP
#define KOCH_HPP

#include <forward_list>
#include <vector>
#include <complex>

#include <SDLO/SDL.hpp>
#include <SDLO/Point.hpp>


class Koch
{
public:

  Koch(int n, int step);

  ~Koch();

  const SDLO::Coord& getOffset() const;

  double getZoom() const;
  
  std::vector<SDLO::Point> getEdges(int, int) const;

  Koch& increment();

  Koch& decrement();

  Koch& zoomIn();

  Koch& zoomOut();

  Koch& move(int x, int y);

private:
  
  std::forward_list<std::complex<double>> m_vertex;

  uint m_max {0};
  
  uint m_current {0};

  double m_zoom {1};
  
  SDLO::Coord m_offset {0, 0};

};

#endif
