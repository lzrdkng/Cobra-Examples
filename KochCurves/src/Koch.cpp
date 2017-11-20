#include "Koch.hpp"

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

std::vector<SDL::Pair<SDL::Point>> Koch::getEdges() const
{
  std::vector<SDL::Pair<SDL::Point>> edges;

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
      edges.push_back({SDL::cartesianToScreen(*it, 500, 500),SDL::cartesianToScreen(*n_it, 500, 500)});
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

  return *this;
}

Koch& Koch::decrement()
{
  if (m_current != 0) --m_current;
  return *this;
}
