#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

constexpr int SCR_H = 500;
constexpr int SCR_W = 500;


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
    SDL_RenderDrawPointF(rend, i.x, i.y);
    
  }

}

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

  auto points = gen_points(0,250, 10, 0);
  

  while(running()){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);


    draw_points(rend, points);
    
    SDL_RenderPresent(rend);
  }

  for(const auto &i: points){
    std::cout << i.x << "\n";
  }


  SDL_DestroyWindow(win);
  SDL_DestroyRenderer(rend);

  SDL_Quit();

  
  return 0;
}
