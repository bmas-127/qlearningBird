#ifndef MULTI_PIPE_HPP_INCLUDED
#define MULTI_PIPE_HPP_INCLUDED

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "pipe.hpp"

using namespace std;

class Pipe;

class multi_pipe
{
private:
    Pipe *pipes;
    int head, tail;
public:
    multi_pipe();
    ~multi_pipe();
    void calculate(int);
    void draw();
    pair<int, int> pipe_pos();
};



#endif // MULTI_PIPE_HPP_INCLUDED
