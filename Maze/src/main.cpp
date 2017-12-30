#include "MazeApplication.hpp"

#include <SDLO/Window.hpp>
#include <SDLO/Renderer.hpp>

using namespace std;

int main()
{

  MazeApplication app(SDLO::InitVideo);

  SDLO::Window window("Maze", 640, 480,
		     SDLO::WindowResizable|SDLO::WindowShown);

  SDLO::Renderer render(window, SDLO::RendererAccelerated);


  app.run(window, render);
}



