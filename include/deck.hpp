#pragma once

#include "clanCard.hpp"
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

class Deck {
public:
  Deck();

  ClanCard draw() {
    // Return the top card and remove it from the deck
    return cards[--top];
  }

  bool isEmpty() const { return top == 0; }

private:
  ClanCard cards[54];
  int top{54}; // Index of the top card in the deck
};