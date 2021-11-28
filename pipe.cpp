#include <iostream>
#include <random>
#include "pipe.hpp"

#define PIPE_WIDTH  90
#define PIPE_HEIGHT 468
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GAP 180

using namespace std;

Pipe::Pipe()
{
    upper_img = lower_img = nullptr;
    upper_img = al_load_bitmap("image/upper_pipe.PNG");
    lower_img = al_load_bitmap("image/lower_pipe.PNG");
    if(!upper_img || !lower_img) cout << "pipe err" << endl;

//    al_draw_bitmap_region(img, 0, 0, 20, 20, pos_x, pos_y, 0);
}

void Pipe::draw()
{
    al_draw_bitmap_region(upper_img, 0, PIPE_HEIGHT - crack, PIPE_WIDTH, PIPE_HEIGHT, pos_x, 0, 0);
    al_draw_bitmap_region(lower_img, 0, 0, PIPE_WIDTH, SCREEN_HEIGHT - crack - GAP, pos_x, crack + GAP, 0);
}

int Pipe::calculate()
{
    pos_x -= 5;
    if(pos_x < -1 * PIPE_WIDTH) return 0;
    return 1;
}

Pipe::~Pipe()
{
    al_destroy_bitmap(upper_img);
    al_destroy_bitmap(lower_img);
    cout << "fuck done" << endl;
}









