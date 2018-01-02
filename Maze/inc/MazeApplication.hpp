#ifndef MAZEAPPLICATION_HPP
#define MAZEAPPLICATION_HPP

#include <SO/SDL.hpp>
#include <SO/Window.hpp>
#include <SO/Renderer.hpp>

#include "Maze.hpp"

class MazeApplication
{
public:

  explicit MazeApplication(SO::Init flags);

    virtual ~MazeApplication();

    void run(SO::Window& window, SO::Renderer& render);

protected:

    void generateMaze();

    void drawMaze(SO::Renderer& renderer);

    void windowResized(const SO::Window& window);

private:

    Maze maze;

    uint width {0};
    uint height {0};

    float paddingX {0.0};
    float paddingY {0.0};

    uint nx {32};
    uint ny {32};

};

#endif // MAZEAPPLICATION_HPP
