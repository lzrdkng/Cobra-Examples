#ifndef MAZEAPPLICATION_HPP
#define MAZEAPPLICATION_HPP

#include <SDLO/SDL.hpp>
#include <SDLO/Window.hpp>
#include <SDLO/Renderer.hpp>

#include "Maze.hpp"

class MazeApplication
{
public:

    explicit MazeApplication(SDLO::InitFlags flags);

    virtual ~MazeApplication();

    void run(SDLO::Window& window, SDLO::Renderer& render);

protected:

    void generateMaze();

    void drawMaze(SDLO::Renderer& renderer);

    void windowResized(const SDLO::Window& window);

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
