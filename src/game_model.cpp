/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "game_model.hpp"

#include <QDebug>
#include <QList>

#include "card_model.hpp"
#include "deck_model.hpp"
#include "player_model.hpp"
#include "stone_model.hpp"

GameModel::GameModel() {
  for (int i = 0; i < STONE_COUNT; i++) {
    stones.append(new StoneModel());
  }
  deck = new DeckModel();
  players[0] = new PlayerModel(0);
  players[1] = new PlayerModel(1);

  for (int cardsDrawn = 0; cardsDrawn < 6; cardsDrawn++) {
    players[0]->pickCard(deck->draw());
    players[1]->pickCard(deck->draw());
  }
}

void GameModel::setTurn(size_t turn) {
  m_turn = turn;
  emit turnChanged(turn);
}

void GameModel::nextTurn() {
  m_turn++;
  qDebug() << "Next turn";
  for (StoneModel* stone : stones) {
    if (!stone->isClaimed()) {
      stone->claims(getPlayer());
      stone->claims(getEnemy());
    }
  }
  emit turnChanged(m_turn);
}

bool GameModel::isWinner(PlayerModel* player) {
  int claimed = 0;
  int claimedAdjacent = 0;
  for (StoneModel* stone : stones) {
    if (stone->isClaimedBy(player)) {
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

void GameModel::setRobot(PlayerModel* robot) {
  QList<CardModel*> cards = players[1]->getCards();
  for (CardModel* card : cards) {
    robot->pickCard(card);
  }
  players[1] = robot;
}
