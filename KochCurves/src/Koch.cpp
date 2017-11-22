#include "Koch.hpp"
#include <iostream>
#include <cmath>

const double PI = 3.14159265358979323846;
const double E  = 3.14159265358979323846/3;

Koch::Koch(int n, int step) : m_vertex()
{
  double angle = 2 * PI / n;

  for (int i=0; i<=n; ++i)
  {
    m_vertex.push_front(std::complex<double> {step * std::cos(angle * i),
	  step * std::sin(angle * i)}
      );
  }
}


Koch::~Koch() { }


const SDL::Coord& Koch::getOffset() const
{
  return m_offset;
}

double Koch::getZoom() const
{
  return m_zoom;
}

std::vector<SDL::Point> Koch::getEdges(int width, int height) const
{
  std::vector<SDL::Point> edges;

  uint delta = static_cast<int>(std::round(std::pow(4, m_max - m_current)));
  
  for (auto it = m_vertex.begin(); it!=m_vertex.end();)
  {
    auto n_it = it;
    
    for (uint i = 0; i < delta && n_it != m_vertex.end(); ++i)
    {
      ++n_it;
    }

    if (n_it != m_vertex.end())
    {
      edges.push_back(
	  SDL::cartesianToScreen(*it,
				 width, height,
				 m_offset,
				 m_zoom));
      edges.push_back(
	    SDL::cartesianToScreen(*n_it,
				   width, height,
				   m_offset,
				   m_zoom));
			
    }

    it = n_it;
  }

  return edges;
}

Koch& Koch::increment()
{

  if (m_current != m_max)
  {
    ++m_current;
    return *this;
  }

  m_max = ++m_current;
  
  for (auto it = m_vertex.begin(); it!=m_vertex.end(); ++it)
  {
    auto n_it = it;

    if (++n_it != m_vertex.end())
    {
      std::complex<double> z = *it - *n_it;

      double d = std::abs(z);
      double a = std::arg(z);

      std::complex<double> u = {std::cos(a), std::sin(a)};
      std::complex<double> v = {std::cos(a + E), std::sin(a + E)};

      std::complex<double> A = *it - d/3 * u;
      std::complex<double> B = *it - 2*d/3 * u;
      std::complex<double> C = *it - d/3 * (u + v);

      it = m_vertex.insert_after(it, A);
      it = m_vertex.insert_after(it, C);
      it = m_vertex.insert_after(it, B);
    }
  }

  int i =0;

  for (auto it=m_vertex.begin(); it!=m_vertex.end(); ++it) ++i;

  std::cout << "Vertices: " << i <<std::endl;

  return *this;
}

Koch& Koch::decrement()
{
  if (m_current != 0) --m_current;
  return *this;
}

Koch& Koch::zoomIn()
{
  m_zoom += 0.5;
  return *this;
}

Koch& Koch::zoomOut()
{
  m_zoom -= 0.5;
  if (m_zoom < 1) m_zoom = 1;
  return *this;
}

Koch& Koch::move(int x, int y)
{
  m_offset += SDL::Coord {static_cast<double>(x), static_cast<double>(y)};
  return *this;
}
