#ifndef BIRD_HPP_INCLUDED
#define BIRD_HPP_INCLUDED

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "keyboard.hpp"

using namespace std;


class bird
{
protected :
    bool *key;
    bool pa;
    float pos_x, pos_y, distance;
    int px, py;
    int score, round;
    short state;
    ALLEGRO_BITMAP *img;
    pair<float, float> ** AI_Front_Board, ** AI_Close_Board;
public :
    bird();
    ~bird();
    int calculate(ALLEGRO_EVENT);
    int FSM(pair<int, int>);
    void draw();
    bool is_collid(pair<int, int>);
    bool point_collid(int, int, pair<int, int>);
    int judgement(keyboard*, pair<int, int>);
    int AI_judgement(pair<int, int>);
};


#endif // BIRD_HPP_INCLUDED
