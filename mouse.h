#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class mouse
{
public:
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT event;
    mouse(){};
};

#endif // MOUSE_H_INCLUDED
