#include "player.hpp"

Player::Player(Deck *deck) {
  for (int i = 0; i < 6; i++) {
    hand[i] = deck->draw();
  }
}