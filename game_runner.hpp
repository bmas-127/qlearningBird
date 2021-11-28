#ifndef GAME_RUNNER_HPP_INCLUDED
#define GAME_RUNNER_HPP_INCLUDED
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

#include "keyboard.hpp"
#include "window.hpp"
#include "bird.hpp"
#include "mouse.h"

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();



void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if (!al_init()) {
        show_err_msg(-1);
    }


    KB = new keyboard;
    WD = new window;
    yellow_bird = new bird;

}


int process_event() {
    ALLEGRO_EVENT key_event = KB->latest_event();

    yellow_bird->calculate(key_event);
    yellow_bird->draw();
    KB->clear();
    return 0;
}

int game_run() {
    if (!KB->queue_empty()) {
        return process_event();
    }
    else if(!WD->queue_empty()) {
        return WD->judge_terminate();
    }
    else{
        return KEEP_RUNNING;
    }
}


void game_destroy() {
    delete KB;
    delete WD;
}



#endif // GAME_RUNNER_HPP_INCLUDED
