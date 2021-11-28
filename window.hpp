#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

class window
{
private :
    const int width = 800;
    const int height = 600;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT event;
public :
    window();
    ~window();
    ALLEGRO_EVENT  latest_event();
    bool queue_empty();
    int judge_terminate();
};

#endif // WINDOW_HPP_INCLUDED
