#include "MazeApplication.hpp"

#include <Cobra/Window.hpp>
#include <Cobra/Renderer.hpp>

using namespace std;

int main()
{

  MazeApplication app(SDL::InitVideo);

  SDL::Window window("Maze", 640, 480,
		     SDL::WindowResizable|SDL::WindowShown);

  SDL::Renderer render(window, SDL::RendererAccelerated);


  app.run(window, render);
}



