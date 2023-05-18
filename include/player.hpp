#pragma once

#include "clanCard.hpp"
#include "deck.hpp"

class Player {
public:
  Player(Deck *deck);
  ClanCard **getHand() { return hand; };

private:
  ClanCard *hand[6];
};