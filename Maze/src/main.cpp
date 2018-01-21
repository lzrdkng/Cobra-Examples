#include "MazeApplication.hpp"

#include <SO/Window.hpp>
#include <SO/Renderer.hpp>

using namespace std;

int main()
{
  MazeApplication app(SO::Init::Video);

  SO::Window window("Maze", SO::Window::Resizable | SO::Window::Shown);

  SO::Renderer render(window, SO::Renderer::Accelerated);

  app.run(window, render);

  return 0;
}



