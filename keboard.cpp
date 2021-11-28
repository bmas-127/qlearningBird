#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "keyboard.hpp"

#define up 0
#define down 1
#define left 2
#define right 3

using namespace std;


keyboard::keyboard()
{
    event_queue = nullptr;
    event_queue = al_create_event_queue();

    if (!event_queue) {
        cout << "load keyboard event Q err" << endl;
    }

    if(!al_install_keyboard()) cout << "keyboard err";

    al_register_event_source(event_queue, al_get_keyboard_event_source() );

}

ALLEGRO_EVENT keyboard::latest_event()
{
    al_wait_for_event(event_queue, &event);

    return event;
}

bool keyboard::queue_empty()
{
    return al_is_event_queue_empty(event_queue);
}

void keyboard::clear()
{
    al_flush_event_queue(event_queue);
}

keyboard::~keyboard()
{
    al_destroy_event_queue(event_queue);
}
