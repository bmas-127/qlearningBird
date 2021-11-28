#include "bird.hpp"
#include "AI_bird.hpp"

#define up 0
#define WAIT 0
#define MOTION 1
#define DROP 2
#define DEATH 3

#define PIPE_WIDTH 90
#define PIPE_GAP 300

AI_BIRD::AI_BIRD()
{
    AI_Front_Board = new pair<int, int> * [20];
    for(int i = 0; i < 20; i ++){
        AI_Front_Board[i] = new pair<int, int> [40];
        for(int j = 0; j < 40; j++){
            AI_Front_Board[i][j].first = AI_Front_Board[i][j].second = 0;
        }
    }
}

int AI_BIRD::AI_judgement( pair<int, int> pipe_pos)
{/*
    if(state == DEATH || state == WAIT){
        state = MOTION;
    }
   if(pipe_pos.first % 20){
        key[up] = false;
   }
   if(pipe_pos.first % 100 == 0){
    key[up] = true;

   }



    if((pipe_pos.first - (int)pos_x) % 20 == 0){
        cout << "dist x = " << pipe_pos.first - (int)pos_x << endl;
        int dist_x = (pipe_pos.first - (int)pos_x) / 20;
        int dist_y = (pipe_pos.second - (int)pos_y) / 20 + 14;
        cout << dist_x << " " << dist_y << endl;
    }


*/

   int dist_x = (pipe_pos.first - (int)pos_x) / 20;
   int dist_y = (pipe_pos.second - (int)pos_y) / 30 + 30;

   /*
cout << "dist_x : " << dist_x << "  dist_y : " << dist_y << endl;
cout << "hop : " << AI_Front_Board[dist_x][dist_y].first << "   do not : " << AI_Front_Board[dist_x][dist_y].second << endl;

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

int AI_BIRD::AI_update(bool success, int dist_x)
{
    int *info;
    int penalty = 30;

    if(success){
        while(!reward.empty()){
            info = reward.top();
            if( info[1] )
                AI_Front_Board[ info[1] ][ info[2] ].first ++;
            else
                AI_Front_Board[ info[1] ][ info[2] ].second ++;
            reward.pop();
        }
    }
    else{
            cout << "here" << endl;
        while(!reward.empty()){
            cout << "fucking loop" << endl;
            info = reward.top();
            cout <<  info[1]  <<  ' ' <<  info[2]  << endl;
            if( info[0] )
                AI_Front_Board[ info[1] ][ info[2] ].first -= penalty;
            else
                AI_Front_Board[ info[1] ][ info[2] ].second -= penalty;
            penalty -= 2;
            reward.pop();
            delete [] info;
         }
         cout << "here" << endl;
         using namespace std;
         state = 0;
    }

    return state;
}










