
#ifndef MAIN_GAME_SHOTS_H
#define MAIN_GAME_SHOTS_H
#include "game_fwd.h"
#include "space_ship.h"
#include <utility>

namespace eclipse {
    struct Shot {
    private:
        int size = 1;
        int x;
        int y;
        int speed = 1;

    public:
        Shot(int x_, int y_) : x(x_), y(y_) {}
        std::pair<int, int> where_is_shot() const;
        void move();
    };
}// namespace eclipse

#endif//MAIN_GAME_SHOTS_H
