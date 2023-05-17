#include "deck.hpp"

Deck::Deck() {
  // TODO : randomize cards order !

  // Seed the random number generator with the current time
  //   srand(time(nullptr));

  // Initialize the deck with random cards
  for (int i = 0; i < 54; i++) {
    int strength = i % 9 + 1; // rand() Random strength between 1 and 9
    ClanCardColor color = static_cast<ClanCardColor>(i % 6); // Random color
    cards[i] = new ClanCard(strength, color);
  }
}
