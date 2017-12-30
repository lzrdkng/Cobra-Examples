#include <iostream>
#include "MazeApplication.hpp"

MazeApplication::MazeApplication(SDLO::InitFlags flags) : maze()
{
  SDLO::init(flags);
}

MazeApplication::~MazeApplication()
{
  SDLO::quit();
}


void MazeApplication::generateMaze()
{
  nx = (width - 2*paddingX)/8;
  ny = (height - 2*paddingY)/8;

  maze.setValues(nx, ny).generateMaze();
}

void MazeApplication::drawMaze(SDLO::Renderer& render)
{
  render.setDrawColor({255, 255, 255});
  render.clear();

  render.setDrawColor({0, 0, 0});
  
  const std::pair<Walls, Walls> walls = maze.getMaze();

  const Walls& wallsH = walls.first;
  const Walls& wallsV = walls.second;

  int x {0}, y {0};

  int stepX = std::round((width  - 2*paddingX)/maze.getNx());
  int stepY = std::round((height - 2*paddingY)/maze.getNy());

  for (auto  it=wallsH.begin(); it!=wallsH.end(); ++it)
  {
    x = stepX * ((*it)%nx) + paddingX;
    y = stepY * ((*it)/nx) + paddingY;

    render.drawLine(x, y, x + stepX, y);
  }

  for (auto  it=wallsV.begin(); it!=wallsV.end(); ++it)
  {
    x = stepX * ((*it)%(nx+1)) + paddingX;
    y = stepY * ((*it)/(nx+1)) + paddingY;

    render.drawLine(x, y, x, y + stepY);
  }

  render.present();
}

void MazeApplication::windowResized(const SDLO::Window& window)
{
  const float P = 0.1F; // Pourcentage of padding

  auto size = window.getSize();

  width  = size.first;
  height = size.second;

  paddingX = P * width;
  paddingY = P * height;
}


void MazeApplication::run(SDLO::Window& window, SDLO::Renderer& render)
{
  SDL_Event event;

  windowResized(window);
  generateMaze();
  drawMaze(render);
  
  do
  {
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) break;
    
    if (event.type == SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
      case SDLK_SPACE:
	generateMaze();
	drawMaze(render);
	break;
      default:
	break;
      }
    }
    
    if (event.type == SDL_WINDOWEVENT)
    {
      switch (event.window.event)
      {
      case SDL_WINDOWEVENT_RESIZED:
      case SDL_WINDOWEVENT_SIZE_CHANGED:
	windowResized(window);
	drawMaze(render);
	break;
      default:
	break;
      }
    }
   
    } while(true);
}

