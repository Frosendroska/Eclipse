#ifndef MAIN_GAME_SPACE_SHIP_H
#define MAIN_GAME_SPACE_SHIP_H

#include "game_fwd.h"
#include <string>
#include <utility>

namespace eclipse {
    struct spaceship {
    private:
        int size = 150;
        int x;
        int y;
        std::string id = "abcd";
        int speed = 14;

    public:
        spaceship(int width, int height) : x(width / 2 - size / 2), y(height - size) {
        }
        std::pair<int, int> get_coordinates() const;
        std::string get_id() const;
        int get_size() const;
        void move(MoveDirection direction);
    };
}// namespace eclipse

#endif// MAIN_GAME_SPACE_SHIP_H
