#include "Maze.hpp"

Maze::Maze() : m_walls(Walls(), Walls()), m_nx(0), m_ny(0) {}

Maze::Maze(uint nx, uint ny)
  : m_walls{iota(1, nx * (ny + 1) - 1), iota(0, ny * (nx + 1))}, m_nx(nx), m_ny(ny)
  {
    this->generateMaze();
  }

Maze::Maze(const Maze& copy)
  : m_walls(copy.getMaze()), m_nx(copy.getNx()), m_ny(copy.getNy())
{

}

Maze::~Maze()
{

}


const std::pair<Walls, Walls>& Maze::getMaze() const
{
  return m_walls;
}

uint Maze::getNx() const
{
  return m_nx;
}

uint Maze::getNy() const
{
  return m_ny;
}

Maze& Maze::setNx(uint nx) { m_nx = nx; return *this; }
Maze& Maze::setNy(uint ny) { m_ny = ny; return *this; }
Maze& Maze::setValues(uint nx, uint ny) { m_nx = nx; m_ny = ny; return *this; }


Walls Maze::determineNeighbours(uint n) const
{
  uint x = n%m_nx;
  uint y = n/m_nx;

  Walls neighbours;

  if (y > 0)
    {
      neighbours.insert(n - m_nx);
    }

  if (y < m_ny - 1)
    {
      neighbours.insert(n + m_nx);
    }

  if (x < m_nx - 1)
    {
      neighbours.insert(n + 1);
    }

  if (x > 0)
    {
      neighbours.insert(n - 1);
    }

  return neighbours;
}

Maze& Maze::generateMaze()
{
  m_walls = {iota(1, m_nx * (m_ny + 1) -1), iota(0, m_ny * (m_nx + 1))};

  srand(time(NULL));

  uint seed = rand() % (m_nx * m_ny);

  Walls neighbours = determineNeighbours(seed);

  Walls cave {seed};
  Walls front {neighbours};

  Walls& wallsH = m_walls.first;
  Walls& wallsV = m_walls.second;

  while (cave.size() != (m_nx * m_ny))
    {
      Walls::const_iterator newCave = randomFromSet(front);

      neighbours = determineNeighbours(*newCave);

      for (Walls::iterator it = neighbours.begin(); it!=neighbours.end(); ++it)
        {
	  if (!cave.count(*it))
            {
	      front.insert(*it);
	      neighbours.erase(it);
            }
        }

      long int d = *newCave - *randomFromSet(neighbours);

      if (d == m_nx)
        {
	  wallsH.erase(*newCave);
        }
      else if (d == -m_nx)
        {
	  wallsH.erase(*newCave + m_nx);
        }
      else if (d == 1)
        {
	  wallsV.erase(*newCave + *newCave/m_nx);
        }
      else
        {
	  wallsV.erase(1 + *newCave + *newCave/m_nx);
        }

      front.erase(newCave);
      cave.insert(*newCave);
    }

  return *this;
}

Walls Maze::iota(uint a, uint b) const
{
  Walls range;

  for (uint i=a; i<b; ++i)
    {
      range.insert(i);
    }

  return range;
}

Walls::const_iterator Maze::randomFromSet(const Walls& set) const
{
  Walls::const_iterator it=set.begin();
  for (uint i=0; i<rand()%set.size(); ++i, ++it);
  return it;
}


