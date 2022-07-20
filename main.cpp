#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

constexpr int SCR_H = 500;
constexpr int SCR_W = 500;

constexpr int MAP_W = 25;
constexpr int MAP_H = 25;

constexpr float TILE_W = SCR_W / MAP_W;
constexpr float TILE_H = SCR_H / MAP_H;

struct point{
  float x, y;
};

std::vector<point> gen_points (float min, float max, size_t range, bool y_only){
  
  std::vector<point> points;
  points.resize(range);


  auto random_pos = [&](){
    float random = min + static_cast <float> (rand() / static_cast <float> (RAND_MAX/max));

    return random;
  };

  
  if(!(y_only)){
    for(auto &i: points){
	i.y = random_pos();
	i.x = random_pos();
    }
  } else {
    int x = 0;
    for(auto &i: points){
	  i.y = random_pos();
	  i.x = x;
	  x++;
    }
  }


  return points;
}





void draw_points(SDL_Renderer* rend, const std::vector<point>& points){

  SDL_SetRenderDrawColor(rend,0,255,0,255);

  for(const auto &i: points){
    //Convert polar coordinates to screen coords
    
    SDL_RenderDrawPointF(rend, i.x * TILE_W, SCR_H - (i.y * TILE_H));
    
  }

}

void line_of_best_fit(SDL_Renderer *rend, const std::vector<point>& points){
  float sumx = 0;
  float sumy = 0;
  float sumxy = 0;
  float sumxx = 0;

  for(const auto &i: points){
    sumx += i.x;
    sumy += i.y;
    sumxy += i.x * i.y;
    sumxx += i.x * i.x;
  }

  float m = ((points.size() * sumxy) - (sumx * sumy)) / ((points.size() * sumxx) - (sumx * sumx));

  float b = (sumy - (m * sumx)) / points.size();

  auto line_function = [&](float x){
    float y = m*x + b;

    return y;
  };


  SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
  SDL_RenderDrawLine(rend, 0 * TILE_W, SCR_H - (line_function(0) * TILE_H)
		     , (MAP_W - 1) * TILE_W, SCR_H - (line_function(MAP_W - 1) * TILE_H));

}

//template <typename F>
//void plot_line(SDL_Renderer *rend, F&& line_function){

  
  

int main(){

  SDL_Window* win = SDL_CreateWindow("line of best fit", 0, 0, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
  SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

  srand(time(NULL));

  auto running = [](){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
	return 0;
      }
    }
    return 1;
  };

  auto points = gen_points(0, 25, MAP_W, 1);
  

  while(running()){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    

    draw_points(rend, points);
    line_of_best_fit(rend, points);
    
    SDL_RenderPresent(rend);
  }

  for(const auto &i: points){
    std::cout << i.x << "\n";
  }

  //std::cout << line_of_best_fit(points) << "\n";


  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(rend);

  SDL_Quit();

  
  return 0;
}
