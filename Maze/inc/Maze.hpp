#ifndef MAZE_HPP
#define MAZE_HPP

// C++ Import
#include <set>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>

// C Import
#include <stdlib.h>
#include <time.h>

typedef std::set<uint> Walls;

class Maze
{

public:

    Maze();

    Maze(uint nx, uint ny);

    Maze(const Maze& copy);

    Maze(Maze&& mvCopy) = delete;
    Maze& operator =(const Maze& assign) = delete;
    Maze& operator =(Maze&& mvAssign) = delete;

    virtual ~Maze();

    const std::pair<Walls, Walls>& getMaze() const;

    uint getNx() const;

    uint getNy() const;

    Maze& setNx(uint nx);
    Maze& setNy(uint ny);
    Maze& setValues(uint nx, uint ny);

    Maze& generateMaze();
/*
    virtual std::vector<uint> solve(uint n);

    virtual std::vector<uint> solveOptimize(uint n);*/

protected:

    std::pair<Walls, Walls> m_walls;


    uint m_nx;
    uint m_ny;


    Walls determineNeighbours(uint n) const;

    Walls iota(uint a, uint b) const;

    Walls::const_iterator randomFromSet(const Walls& set) const;


};


#endif // MAZE_HPP
