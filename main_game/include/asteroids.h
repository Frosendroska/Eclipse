#ifndef MAIN_GAME_ASTEROIDS_H
#define MAIN_GAME_ASTEROIDS_H

#include "game_fwd.h"
#include <cstdlib>
#include <string>
#include <utility>

namespace eclipse {
    struct Asteroid {
    private:
        int x;
        int y = 0;
        int size = 0;
        int lives = 2;
        ObjectState state = kAlive;
        std::string id;
        friend bool operator<(const Asteroid &first, const Asteroid &second);

    public:
        Asteroid(int x, int size, std::string id)
            : x(x), size(size), id(std::move(id)) {
        }

        ObjectState get_state() const;

        void move(int speed);

        std::pair<int, int> get_coordinates() const;// x,y coordinates

        std::string get_id() const;

        int get_size() const;

        void destroy();
    };

}// namespace eclipse

#endif// MAIN_GAME_ASTEROIDS_H
