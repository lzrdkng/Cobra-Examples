#include "MazeApplication.hpp"

#include <SO/Window.hpp>
#include <SO/Renderer.hpp>

using namespace std;

int main()
{
  MazeApplication app(SO::Init::Video);

  SO::Window window("Maze", SO::Wind::Resizable | SO::Wind::Shown);

  SO::Renderer render(window, SO::Render::Accelerated);

  app.run(window, render);

  return 0;
}



