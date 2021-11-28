#include "keyboard.hpp"
#include "window.hpp"
#include "bird.hpp"
#include "pipe.hpp"
#include "AI_bird.hpp"

#define GAME_TERMINATE 666
#define KEEP_RUNNING 668

using namespace std;


keyboard *KB;
window *WD;
bird *yellow_bird;
multi_pipe *pipe;

void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();


int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    printf("Hello world!!!\n");

    while (msg != GAME_TERMINATE) {
        msg = game_run();
        if (msg == GAME_TERMINATE)
            printf("See you, world\n");
    }

    game_destroy();
    return 0;
}

void game_init() {

    WD = new window;
    KB = new keyboard;
    yellow_bird = new bird;
    pipe = new multi_pipe;

}


int process_event() {
    ALLEGRO_EVENT key_event;
    pair<int, int> pipe_pos = pipe->pipe_pos();
    int state;


        state = yellow_bird->AI_judgement(pipe_pos);



/*
    if(KB->queue_empty()){
        state = yellow_bird->FSM(pipe_pos);
    }
    else {
        key_event = KB->latest_event();
        state = yellow_bird->judgement(key_event, pipe_pos);
    }
    */


//    state = yellow_bird->AI_judgement(pipe_pos);
/*
    if(pipe_pos.first == 270){
            cout << "updating 270" << endl;
        state = yellow_bird->AI_update(true, pipe_pos.first);
    }
    else if(state == 3){
            cout << "updating" << endl;
        state = yellow_bird->AI_update(false, pipe_pos.first);
    }
*/
    pipe->calculate(state);
    al_rest(0.001);


    yellow_bird->draw();
    pipe->draw();


    al_draw_rectangle(pipe_pos.first, pipe_pos.second, pipe_pos.first+10, pipe_pos.second+10,  al_map_rgb(30, 30, 30), 2);

    al_flip_display();

    return 0;
}

int game_run() {
    if(!WD->queue_empty()) {
        return WD->judge_terminate();
    }
    else {
        return process_event();
    }
}

void game_destroy() {
    delete KB;
    delete WD;
    delete yellow_bird;
}
