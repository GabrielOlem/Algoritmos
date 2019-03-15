#include <bits/stdc++.h>
using namespace std;

class piece{
    private:
        int x, y;
        bool v;
        void revive(void){
            v = true;
        }
    public:
        piece(int dx, int dy){
            x = dx;
            y = dy;
            v = true;
        }
        void death(void){
            v = false;
        }
        void move(int dx, int dy) = 0;
};

class tower : private piece{
    public:
        void move(int dx, int dy){
            this->x = dx;
            this->y = dy;
        }
};

class pawn : private piece{
    public:
        void move(int dx, int dy){
            this->x = dx+1;
            this->y = dy+1;
        }
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    piece *ptr;
    pawn p;
    tower t;
    ptr = &t;
    ptr = &p;
    return 0;    
}