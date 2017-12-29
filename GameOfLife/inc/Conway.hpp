#ifndef CONWAY_HPP
#define CONWAY_HPP

#include <vector>
#include <random>

class Conway
{
public:
  
  explicit Conway(double p , int width, int height)
  {
    // https://stackoverflow.com/questions/25176423
    std::random_device random;
    std::mt19937 generator(random());
    std::bernoulli_distribution distribution(p);

    for (int i=0; i<height; ++i)
    {
      cells.push_back(std::vector<int> {});
      
      for (int j=0; j<width; ++j)
      {
	cells[i].push_back(distribution(generator));
      }
    }
    
  }
  
  const std::vector<std::vector<int>>& getCells() const { return cells; }

  Conway& step()
  {
    std::vector<std::vector<int>> nextGeneration(cells);

    for (uint i=0; i<cells.size(); ++i)
    {
      for (uint j=0; j<cells[i].size(); ++j)
      {

	uint n = countNeighbors(i, j);
	
	if  (cells[i][j])
	{
	  if (n == 2 || n == 3)
	    nextGeneration[i][j] = 1;
	  else
	    nextGeneration[i][j] = 0;
	}
	else
	{
	  if (n == 3)
	    nextGeneration[i][j] = 1;
	  else
	    nextGeneration[i][j] = 0;
	}
      }
    }
    
    cells = nextGeneration;

    return *this;
  }
  
private:
  
  std::vector<std::vector<int>> cells;

  uint countNeighbors(uint i, uint j) const
  {
     uint count = 0;

     if  (i > 0) 
       count += cells[i-1][j];
	 
     if  (i >0 && j > 0)
       count += cells[i-1][j-1];
     
     if  (i >0 && j < cells[i].size() - 1)
       count += cells[i-1][j+1];
     
     if  (j > 0)
       count += cells[i][j-1];
     
     if  (j > 0 && i < cells.size() - 1)
       count += cells[i+1][j-1];
     
     if  (i < cells.size() - 1)
       count += cells[i+1][j];
     
     if  (j < cells[i].size() - 1)
       count += cells[i][j+1];
     
     if  (i < cells.size() - 1 && j < cells[i].size() - 1)
       count += cells[i+1][j+1];
     
     return count;
  }
  
};


#endif
