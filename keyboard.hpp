#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#define up 0
#define down 1
#define left 2
#define right 3

using namespace std;

class keyboard
{
private :
    bool *key;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT event;
public :
    keyboard();
    ~keyboard();
    ALLEGRO_EVENT  latest_event();
    bool queue_empty();
    void clear();
};

#endif // KEYBOARD_H_INCLUDED
