/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "player_model.hpp"

void PlayerModel::removeCard(CardModel *card) {
  if (!m_cards.removeOne(card)) throw 1;
  emit changedCards(m_cards);
}

void PlayerModel::pickCard(CardModel *card) {
  m_cards.append(card);
  emit changedCards(m_cards);
}
