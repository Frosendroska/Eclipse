#include "God.h"
#include <Modification_store.h>
#include <iostream>
#include <memory>
#include <thread>
#include "game.h"
#include "game_fwd.h"

extern Modification_store train;

void God::show_menu() {
    menu = new game_window();
    menu->show_menu_first();
}

void God::close_menu() const {
    menu->close();
}

void God::show_game_field() {
    game_view = new main_window();
    game_view->make_field();
    menu->hide();
    game_view->show();
    selection_window = new Selection();
    // select_game_controller(eclipse::Key);
    selection_window->show();
}

void God::close_game_field() const {
    game_view->close();
    menu->show();
}

void God::set_object(int x,
                     int y,
                     int size,
                     const std::string &hash,
                     const std::string &object_name) const {
    game_view->set(x, y, size, hash, object_name);
}

void God::move_object(int x, int y, const std::string &hash) const {
    game_view->move(x, y, hash);
}

void God::delete_object(const std::string &hash) const {
    game_view->delete_obj(hash);
}

void God::clicked_on_start() {
    game = std::make_unique<eclipse::Game>();  //создаем новую игру
    //запустить таймер???

    close_menu();
    show_game_field();
    make_changes_in_qt();

    game_view->set_lives();
    game_view->set_timer();
}

void God::clicked_on_exit() {
    game = nullptr;
    //просто вывести таймер??
    close_menu();
}

void God::make_changes_in_qt() const {
    for (auto &i : game->changes) {
        if (i.new_coordinates.first == -1 && i.new_coordinates.second == -1) {
            delete_object(i.id);
        } else if (i.object_name.empty()) {
            move_object(i.new_coordinates.first, i.new_coordinates.second,
                        i.id);
        } else {
            set_object(i.new_coordinates.first, i.new_coordinates.second,
                       i.size, i.id, i.object_name);
        }
    }
    game->changes.clear();
}

void God::make_move_in_logic() const {
    auto [direction, steps] = train.give_changes();
    //    std::cerr << "train"
    //              << " " << direction << '\n';
    game->make_move(direction);  //наверное, потом стоит убрать цикл
    make_changes_in_qt();
}

void God::shoot_in_God() const {
    game->shoot();
}

void God::select_game_controller(eclipse::Controllers controller_) {
    /*
      switch (controller_) {
          case eclipse::Key:
              controller.key_controller = new Key_Controller();
              break;
          case eclipse::Arduino: {
              ReadingFromPort::Ports my_ports;
              std::string port = my_ports.get_arduino_port();
              controller.arduino_controller = new
      ReadingFromPort::Arduino(port); } break; default: break;
      }
      */
    if (controller_ == eclipse::Key) {
        controller.key_controller = new Key_Controller();
    } else {
        ReadingFromPort::Ports my_ports;
        std::string port = my_ports.get_arduino_port();
        controller.arduino_controller = new ReadingFromPort::Arduino(port);
        //            controller.arduino_controller->make_a_move();
        //        auto w = [&](){
        //          for(;;){
        //              std::cerr << "!!" << std::endl;
        //          }
        //        };

        std::thread ta([]() {

        });
    }
    //подумать откуда еще можно запустить, пока нелогично
    game_view->start_timer();
}

void God::decrease_lives_ui() const {
    game_view->decrease_lives();
}