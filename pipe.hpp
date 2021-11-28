#ifndef PIPE_HPP_INCLUDED
#define PIPE_HPP_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "multi_pipe.hpp"

class Pipe
{
private :
    ALLEGRO_BITMAP *upper_img, *lower_img;
    int crack;
    int pos_x;
public :
    Pipe();
    ~Pipe();
    void draw();
    int calculate();
    friend class multi_pipe;
};


#endif // PIPE_HPP_INCLUDED
