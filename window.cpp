#include "window.hpp"

#define GAME_TERMINATE 666
#define KEEP_RUNNING 668

window::window()
{
    if(!al_init()) std::cout << "game init failed" << std::endl;

    display = nullptr;
    event_queue = nullptr;
    display = al_create_display(width, height);
    event_queue = al_create_event_queue();
    al_init_font_addon();

    if(!al_init_primitives_addon()) std::cout << "init primitive err" << std::endl;\
    if(!al_init_image_addon()) std::cout << "init image err" << std::endl;
    if(!al_init_ttf_addon()) std::cout << "init ttf err" << std::endl;
    if(!display || !event_queue) std::cout << "init window err" << std::endl;

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_clear_to_color(al_map_rgb(20, 20, 60));
    al_flip_display();
}

window::~window()
{
    cout << "dick";
    al_destroy_display(display);
}

bool window::queue_empty()
{
    return al_is_event_queue_empty(event_queue);
}

int window::judge_terminate()
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return GAME_TERMINATE;
    }
    else{
        return KEEP_RUNNING;
    }
}




