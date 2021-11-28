#ifndef AI_BIRD_HPP_INCLUDED
#define AI_BIRD_HPP_INCLUDED
#include <stack>
#include <iostream>
#include "bird.hpp"


class AI_BIRD : public bird
{
private :
    pair<int, int> ** AI_Front_Board, ** AI_Close_Board;
    stack<int*> reward;
public :
    AI_BIRD();
    int AI_judgement(pair<int, int>);
    int AI_update(bool, int);
};




#endif // AI_BIRD_HPP_INCLUDED
