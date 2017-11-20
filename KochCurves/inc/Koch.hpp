#ifndef KOCH_HPP
#define KOCH_HPP

#include <forward_list>
#include <vector>
#include <complex>

#include <Cobra/SDL.hpp>
#include <Cobra/Point.hpp>


class Koch
{
public:

  Koch(int n, int step);

  ~Koch();

  std::vector<SDL::Pair<SDL::Point>> getEdges() const;

  Koch& increment();

  Koch& decrement();

private:
  
  std::forward_list<std::complex<double>> m_vertex;

  uint m_max {0};
  uint m_current {0};

};

#endif
