#include "MazeApplication.hpp"

MazeApplication::MazeApplication(SDL::InitFlags flags) : maze()
{
    SDL::init(flags);
}

MazeApplication::~MazeApplication()
{
    SDL::quit();
}


void MazeApplication::generateMaze()
{
    nx = (width - 2*paddingX)/8;
    ny = (height - 2*paddingY)/8;

    maze.setValues(nx, ny).generateMaze();
}

void MazeApplication::drawMaze(SDL::Renderer& render)
{
    std::vector<SDL::Pair<SDL::Point>> vector_walls;

    const std::pair<Walls, Walls> walls = maze.getMaze();

    const Walls& wallsH = walls.first;
    const Walls& wallsV = walls.second;

    int x {0}, y {0};

    float stepX = (width  - 2*paddingX)/maze.getNx();
    float stepY = (height - 2*paddingY)/maze.getNy();

    for (Walls::iterator it=wallsH.begin(); it!=wallsH.end(); ++it)
    {
        x = stepX * ((*it)%nx) + paddingX;
        y = stepY * ((*it)/nx) + paddingY;

        SDL::Pair<SDL::Point> points(SDL::Point {x, y}, SDL::Point {x+stepX, y});

        vector_walls.push_back(points);
    }

    for (Walls::iterator it=wallsV.begin(); it!=wallsV.end(); ++it)
    {
        x = stepX * ((*it)%(nx+1)) + paddingX;
        y = stepY * ((*it)/(nx+1)) + paddingY;

        SDL::Pair<SDL::Point> points(SDL::Point {x, y}, SDL::Point {x, y+stepY});

        vector_walls.push_back(points);
    }

    render.setDrawColor(SDL::Color {255, 255, 255});
    render.clear();

    render.setDrawColor(SDL::Color {0, 0, 0});
    render.drawLines(vector_walls);

    render.present();
}

void MazeApplication::windowResized(const SDL::Window& window)
{
    const float P = 0.1F; // Pourcentage of padding

    SDL::Pair<int> size = window.getSize();

    width  = size.getFirst();
    height = size.getSecond();

    paddingX = P * width;
    paddingY = P * height;
}


void MazeApplication::run(SDL::Window& window, SDL::Renderer& render)
{
    SDL_Event event;

    windowResized(window);
    generateMaze();
    drawMaze(render);


    do
    {
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            break;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                generateMaze();
                drawMaze(render);
                continue;
            }

            SDL_FlushEvent(SDL_KEYDOWN);
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                windowResized(window);
                drawMaze(render);
                continue;
            }
        }

    } while(true);

}

