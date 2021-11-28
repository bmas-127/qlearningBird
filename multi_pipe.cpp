#include <random>
#include "multi_pipe.hpp"

#define PIPE_WIDTH 90
#define PIPE_GAP 400
#define PIPE_NUM 5
#define START_POSITION_X 500
#define GAP 180

#define WAIT 0
#define MOTION 1
#define DROP 2


multi_pipe::multi_pipe()
{
    head = 0;
    tail = PIPE_NUM - 1;
    pipes = new Pipe [PIPE_NUM];


    std::random_device rd;
    std::default_random_engine gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(80, 300);

    for(int i = 0; i < PIPE_NUM; i++){
        pipes[i].pos_x = START_POSITION_X + i * PIPE_GAP;
        pipes[i].crack = dis(gen);
    }
}

multi_pipe::~multi_pipe()
{
    delete [] pipes;
}

void multi_pipe::calculate(int state)
{
    switch(state)
    {
        case WAIT :
            for(int i = 0; i < PIPE_NUM; i++){
                pipes[i].pos_x = START_POSITION_X + i * PIPE_GAP;
            }
            head = 0;
            tail = PIPE_NUM - 1;
            break;

        case MOTION :
            for(int i = 0; i < PIPE_NUM; i++){
                pipes[i].pos_x -= 5;
            }
            break;
    }


    if(pipes[head].pos_x < PIPE_WIDTH * (-1)){
        std::random_device rd;
        std::default_random_engine gen = std::default_random_engine(rd());
        std::uniform_int_distribution<int> dis(40, 500);
        pipes[head].crack = rand() % 300 + 40;

        pipes[head].pos_x = pipes[tail].pos_x + PIPE_GAP;
        head = (head + 1) % PIPE_NUM;
        tail = (tail + 1) % PIPE_NUM;
    }
}

void multi_pipe::draw()
{
    for(int i = 0; i < PIPE_NUM; i++){
        pipes[i].draw();
    }
}

pair<int, int> multi_pipe::pipe_pos()
{
    if(pipes[head].pos_x + PIPE_WIDTH > 180)
        return make_pair(pipes[head].pos_x + PIPE_WIDTH, pipes[head].crack + GAP);
    else
        return make_pair(pipes[(head+1)%PIPE_NUM].pos_x + PIPE_WIDTH, pipes[(head+1)%PIPE_NUM].crack + GAP);
}








