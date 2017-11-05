#ifndef MAZEAPPLICATION_HPP
#define MAZEAPPLICATION_HPP

#include <Cobra/SDL.hpp>
#include <Cobra/Window.hpp>
#include <Cobra/Renderer.hpp>

#include "Maze.hpp"

class MazeApplication
{
public:

    explicit MazeApplication(SDL::InitFlags flags);

    virtual ~MazeApplication();

    void run(SDL::Window& window, SDL::Renderer& render);

protected:

    void generateMaze();

    void drawMaze(SDL::Renderer& renderer);

    void windowResized(const SDL::Window& window);

private:

    Maze* maze;

    uint width {0};
    uint height {0};

    float paddingX {0.0};
    float paddingY {0.0};

    uint nx {32};
    uint ny {32};

};

#endif // MAZEAPPLICATION_HPP
