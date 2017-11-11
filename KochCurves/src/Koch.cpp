#include "Koch.hpp"

#include <cmath>

const double PI = 3.14159265358979323846;
const double E  = 3.14159265358979323846/2.71828182845904523536;

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

    std::forward_list<std::complex<double>>::const_iterator n_it = m_vertex.begin();

    for (auto it = n_it; it!=m_vertex.end(); ++it)
    {
        if (++n_it != m_vertex.end())
        {
            SDL::Coord A = SDL::cartesianToScreen(*it, 500, 500);
            SDL::Coord B = SDL::cartesianToScreen(*n_it, 500, 500);

            edges.push_back(
                        SDL::Pair<SDL::Point>
                        {
                            SDL::Point(static_cast<int>(std::real(A)), static_cast<int>(std::imag(A))),
                            SDL::Point(static_cast<int>(std::real(B)), static_cast<int>(std::imag(B)))
                        }
                           );
        }
    }

    return edges;
}

Koch& Koch::iterate()
{
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
