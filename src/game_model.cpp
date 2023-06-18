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

GameModel::GameModel() : players{PlayerModel(0), PlayerModel(1)} {
  // Initialize the deccardsk with random cards
  QMetaEnum metaEnum = QMetaEnum::fromType<ClanCardModel::CardColor>();
  for (int i = 0; i < metaEnum.keyCount(); ++i) {
    for (int strength = 1; strength <= 9; strength++) {
      auto color = static_cast<ClanCardModel::CardColor>(metaEnum.value(i));
      CardModel* card = new ClanCardModel(strength, color);
      cards.append(card);
      deck.addCard(card);
    }
  }
  deck.shuffle();
  for (int cardsDrawn = 0; cardsDrawn < 6; cardsDrawn++) {
    players[0].pickCard(deck.draw());
    players[1].pickCard(deck.draw());
  }
}

GameModel::~GameModel() {
  while (!cards.isEmpty()) {
    delete cards.takeAt(0);
  }
}

void GameModel::nextTurn() {
  qDebug() << "Next turn";
  for (size_t i = 0; i < STONE_COUNT; i++) {
    if (!stones[i].isClaimed()) {
      stones[i].claims(getPlayer());
      stones[i].claims(getEnemy());
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
    if (stones[i].isClaimedBy(player)) {
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
