#include "classes_intro.hpp"
#include "concepts/mylogging.hpp"
#include <glog/logging.h>

int Player::object_count = 0;
int Player::object_count_since_starting = 0;

void classes_conccepts_hub() {
    /* Player player(x = 10, y = 20, speed = 200, verbose = verbose); */
    /* player.display(); */

    int x, y, speed;
    bool verbose = true;

    for (int i = 0; i < 10; i++) {
        Player p = Player(x = i + 200, y = i + 100, speed = i + 1000, verbose);
        // p.display();
    }

    Player p2 = Player(verbose);
    Player p3 = Player(verbose);
    p2.display();
    p3.display();

    Player player(x = 10, y = 20, speed = 200, verbose);
    for (int i = 0; i < 10; i++) {
        player.set_x(10 + i);
        player.set_y(10 - i);
        player.set_speed(100 + i);
        player.display();
    }
}

Player::Player(int x, int y, int speed, bool verbose)
    : x{x},
      y{y},
      speed{speed},
      verbose{verbose} {
    object_count_since_starting++;
    object_id = object_count_since_starting;
}

Player::Player(bool verbose)
    : x{0},
      y{0},
      speed{0},
      verbose{verbose} {
    object_count_since_starting++;
    object_id = object_count_since_starting;
}

Player::Player(const Player& other)
    : x{other.x},
      y{other.y},
      speed{other.speed},
      verbose{other.verbose},
      object_id{other.object_count_since_starting++} {
    object_id = object_count_since_starting;
}

Player::Player(Player&& other) noexcept
    : x{other.x},
      y{other.y},
      speed{other.speed},
      verbose{other.verbose},
      object_id{other.object_count_since_starting++} {}

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        speed = other.speed;
        verbose = other.verbose;
        object_count_since_starting++;
        object_id = object_count_since_starting;
        // object_id should not change in copy assignment
    }
    return *this;
}

Player& Player::operator=(Player&& other) noexcept {
    if (this != &other) {
        x = other.x;
        y = other.y;
        speed = other.speed;
        verbose = other.verbose;
        object_count_since_starting++;
        object_id = object_count_since_starting + 1;

        // object_id should not change in move assignment
        other.x = 0;
        other.y = 0;
        other.speed = 0;
    }
    return *this;
}

Player::~Player() {
    // Destructor logic (if any)
    object_count--;
    if (this->verbose) {
        LOG(INFO) << RED << "OBJECT::" << BLUE << BLUE "[" << RED << this->object_id << BLUE << "]"
                  << " is destroyed ..." << RESET;
    }
}

int Player::get_x() const { return x; }
void Player::set_x(int x) { this->x = x; }
int Player::get_y() const { return y; }
void Player::set_y(int y) { this->y = y; }
int Player::get_speed() const { return speed; }
void Player::set_speed(int speed) { this->speed = speed; }

void Player::display() {
    LOG(INFO) << RED << " Player " << BLUE "[" << MAGENTA << object_id << BLUE << "]" << YELLOW
              << " at (" << BLUE << x << RED << ", " << BLUE << y << YELLOW << ") with speed "
              << MAGENTA << speed << RESET;
}
