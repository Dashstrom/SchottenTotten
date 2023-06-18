/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "deck_model.hpp"

#include <algorithm>
#include <random>

#include "clan_card_model.hpp"

void DeckModel::shuffle() {
  // Shuffle cards
  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(m_cards.begin(), m_cards.end(), gen);
}
