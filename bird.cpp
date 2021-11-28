#include "bird.hpp"
#include "keyboard.hpp"
using namespace std;

#define up 0
#define down 1
#define left 2
#define right 3

#define WAIT 0
#define MOTION 1
#define DROP 2
#define DEATH 3

#define alpha 0.3
#define gamma 0.6

#define BITD_SIZE 45
#define PIPE_WIDTH 90
#define PIPE_GAP 180

#define COLLID 0
#define KEY_UP 1

bird::bird()
{
    pos_x = 190;
    pos_y = 240;
    state = WAIT;
    key = new bool [4];

    px = 20;
    py = 16;
    pa = false;

    round = score = 0;

    img = nullptr;
    img = al_load_bitmap("image/bird.jpg");
    if(!img) cout << "bird err" << endl;


    AI_Front_Board = new pair<float, float> * [21];

    // QTABLE INIT
    for(int i = 0; i < 21; i ++){
        AI_Front_Board[i] = new pair<float, float> [40];
        for(int j = 0; j < 40; j++){
            AI_Front_Board[i][j].first = AI_Front_Board[i][j].second = 0;
        }
    }
}

bird::~bird()
{
    al_destroy_bitmap(img);
    delete [] key;
}


int bird::judgement(keyboard* KB, pair<int, int> pipe_pos){

    if((pipe_pos.first - (int)pos_x) % 20 == 0){
        cout << "dist x = " << pipe_pos.first - (int)pos_x << endl;
        int dist_x = (pipe_pos.first - (int)pos_x) / 20;
        int dist_y = (pipe_pos.second - (int)pos_y) / 20 + 14;
        cout << dist_x << " " << dist_y << endl;
    }

    if(! KB->queue_empty()){
        calculate( KB->latest_event() );
    }

    return FSM(pipe_pos);
}

int bird::AI_judgement(pair<int, int> pipe_pos)
{
    if(state == DEATH){
        state = WAIT;
        pos_y = 240;
        int dist_x = (pipe_pos.first - (int)pos_x) / 20;
        int dist_y = (pipe_pos.second - (int)pos_y) / 20 + 15;


        if(pa){
            AI_Front_Board[px][py].first = (1 - alpha) * AI_Front_Board[px][py].first + alpha * ( (-100) + gamma *  std::max(AI_Front_Board[dist_x][dist_y].first, AI_Front_Board[dist_x][dist_y].second));;
        }else
            AI_Front_Board[px][py].second = (1 - alpha) * AI_Front_Board[px][py].second + alpha * ( (-100) + gamma * std::max(AI_Front_Board[dist_x][dist_y].first, AI_Front_Board[dist_x][dist_y].second));;


    }else if (state == WAIT){
        px = 20;
        py = 16;
        pa = false;
        distance = 0;
        state = MOTION;

        cout << "round = " << round << " " << "score = " << score << endl;

        round ++;
        score = 0;
    }
    else{
       if(pipe_pos.first % 20){
            key[up] = false;
            return FSM(pipe_pos);
       }


       // cout << "dist x = " << pipe_pos.first - (int)pos_x << endl;
        int dist_x = (pipe_pos.first - (int)pos_x) / 20;
        int dist_y = (pipe_pos.second - (int)pos_y) / 20 + 16;
       // cout << dist_x << " " << dist_y << "board = "     << endl;


        // reward
        if(pa)
            AI_Front_Board[px][py].first = (1 - alpha) * AI_Front_Board[px][py].first + alpha * ( 1 + gamma * std::max(AI_Front_Board[dist_x][dist_y].first, AI_Front_Board[dist_x][dist_y].second));
        else
            AI_Front_Board[px][py].second = (1 - alpha) * AI_Front_Board[px][py].second + alpha * ( 1 + gamma * std::max(AI_Front_Board[dist_x][dist_y].first, AI_Front_Board[dist_x][dist_y].second));


        if(AI_Front_Board[dist_x][dist_y].first > AI_Front_Board[dist_x][dist_y].second){
            key[up] = true;
            pa = true;
        }else{
            key[up] = false;
            pa = false;
        }

        px = dist_x;
        py = dist_y;

        if(dist_x == 0){
            score ++;
        }





      //  cout << "dist_x : " << dist_x << "  dist_y : " << dist_y << endl;
     //   cout << "hop : " << AI_Front_Board[dist_x][dist_y].first << "   do not : " << AI_Front_Board[dist_x][dist_y].second << endl;


    }


/*
   if(AI_Front_Board[dist_x][dist_y].first > AI_Front_Board[dist_x][dist_y].second){
        key[up] = true;
   }
   else if(AI_Front_Board[dist_x][dist_y].first == AI_Front_Board[dist_x][dist_y].second){
        key[up] = (dist_y < 30) ? true : false;
   }
   else{
        key[up] = false;
   }

   int *info = new int [3];
   info[0] = key[up];
   info[1] = dist_x;
   info[2] = dist_y;
   reward.push(info);
   cout << "AI judgement complete" << endl << endl;

   return FSM(pipe_pos);
   */


        return FSM(pipe_pos);
}




/*
int bird::judgement(ALLEGRO_EVENT event, pair<int, int> pipe_pos){



    if((int)pos_x % 30 == 0){
        int dist_x = (pipe_pos.first - (int)pos_x) / 20;
        int dist_y = (pipe_pos.second - (int)pos_y) / 20 + 14;
        cout << dist_x << " " << dist_y << endl;
    }
    calculate(event);
    return FSM(pipe_pos);
}
*/
int bird::calculate(ALLEGRO_EVENT event)
{
    if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        switch(event.keyboard.keycode){
            case ALLEGRO_KEY_UP :
                key[up] = true;
                break;
            case ALLEGRO_KEY_DOWN :
                key[down] = true;
                break;
            case ALLEGRO_KEY_LEFT :
                key[left] = true;
                break;
            case ALLEGRO_KEY_RIGHT :
                key[right] = true;
                break;
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        switch(event.keyboard.keycode){
            case ALLEGRO_KEY_UP :
                key[up] = false;
                break;
            case ALLEGRO_KEY_DOWN :
                key[down] = false;
                break;
            case ALLEGRO_KEY_LEFT :
                key[left] = false;
                break;
            case ALLEGRO_KEY_RIGHT :
                key[right] = false;
                break;
        }
    }
}

int bird::FSM(pair<int, int> pipe_pos)
{
//    cout << "in fsm" << endl << endl;

    switch(state){
        case WAIT :
            if(key[up]){
                distance = 0;
                state = MOTION;
            }
            break;
        case MOTION :
            if(is_collid(pipe_pos)){
                state = DEATH;
            }
            else{
                if(key[up]){
                    distance = 11;
                    pos_y -= 10;
                }
                else if(key[down]){
                    state = WAIT;
                }
                else{
                    pos_y -= distance;
                    distance -= 1;
                }
            }
            break;
        case DEATH :
            if(key[up]){
                pos_y = 240;
                state = WAIT;
                printf("keyup\n");
                key[up] = false;
            }
            break;
    }


    pos_x = (int)( pos_x + (int)key[right] * 10 ) % 800;
    pos_x = (int)( pos_x - (int)key[left] * 10 ) % 800;
//    std::cout << key[up] << ' ' << key[down] << ' ' << key[left] << ' ' << key[right] << std::endl;
//    std::cout << pos_x << ' ' << pos_y << std::endl;

    return state;
}

void bird::draw()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(img, pos_x, pos_y, 0);
    al_draw_rectangle(pos_x, pos_y, pos_x+10, pos_y+10,  al_map_rgb(30, 30, 30), 2);

}

bool bird::is_collid(pair<int, int> pipe_pos)
{
    if ( pos_y > 555) return true;
    if ( point_collid(pos_x + 23, pos_y, pipe_pos) ) return true;
    if ( point_collid(pos_x + 23, pos_y, pipe_pos) ) return true;
    if ( point_collid(pos_x, pos_y + 23, pipe_pos) ) return true;
    if ( point_collid(pos_x + 23, pos_y + 23, pipe_pos) ) return true;

    return false;
}

bool bird::point_collid(int x, int y, pair<int, int> pipe_pos)
{
    if(x > pipe_pos.first - PIPE_WIDTH  && x < pipe_pos.first ){
        if(y > pipe_pos.second - PIPE_GAP && y < pipe_pos.second){
            return false;
        }
        return true;
    }
    return false;
}





