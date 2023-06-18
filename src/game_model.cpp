/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "game_model.hpp"

#include <QDebug>
#include <QList>
#include <QMetaEnum>

#include "card_model.hpp"
#include "deck_model.hpp"
#include "player_model.hpp"
#include "stone_model.hpp"

GameModel::GameModel() : m_players{PlayerModel(0), PlayerModel(1)} {
  // Initialize the deccardsk with random cards
  QMetaEnum metaEnum = QMetaEnum::fromType<ClanCardModel::CardColor>();
  for (int i = 0; i < metaEnum.keyCount(); ++i) {
    for (int strength = 1; strength <= 9; strength++) {
      auto color = static_cast<ClanCardModel::CardColor>(metaEnum.value(i));
      CardModel* card = new ClanCardModel(strength, color);
      m_cards.append(card);
      m_deck.addCard(card);
    }
  }
  m_deck.shuffle();
  for (int cardsDrawn = 0; cardsDrawn < 6; cardsDrawn++) {
    m_players[0].pickCard(m_deck.draw());
    m_players[1].pickCard(m_deck.draw());
  }
}

GameModel::~GameModel() {
  while (!m_cards.isEmpty()) {
    delete m_cards.takeAt(0);
  }
}

void GameModel::nextTurn() {
  qDebug() << "Next turn";
  for (size_t i = 0; i < STONE_COUNT; i++) {
    if (!m_stones[i].isClaimed()) {
      m_stones[i].claims(getPlayer());
      m_stones[i].claims(getEnemy());
    }
  }
  if (!isEnd()) {
    m_turn++;
  }
}

bool GameModel::isWinner(PlayerModel& player) {
  int claimed = 0;
  int claimedAdjacent = 0;
  for (size_t i = 0; i < STONE_COUNT; i++) {
    if (m_stones[i].isClaimedBy(player)) {
      claimed += 1;
      claimedAdjacent += 1;
    } else {
      claimedAdjacent = 0;
    }
    if (claimed >= 5 || claimedAdjacent >= 3) {
      return true;
    }
  }
  if (claimed >= 5 || claimedAdjacent >= 3) {
    return true;
  }
  return false;
}

size_t GameModel::getWinnerId() {
  if (isWinner(getPlayer())) {
    return getPlayer().id();
  } else if (isWinner(getEnemy())) {
    return getEnemy().id();
  } else {
    return -1;
  }
}
