/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */

#include "game_robot_model.hpp"

#include <QObject>
#include <QRandomGenerator>

#include "game_model.hpp"

void GameRobotModel::nextTurn() {
  GameModel::nextTurn();
  // robot play
  if (!isEnd()) {
    QList<CardModel*> robotCards = getPlayer().getCards();
    QRandomGenerator* generator = QRandomGenerator::global();
    if (robotCards.size() != 0) {
      int randomIndex = generator->bounded(robotCards.size());
      CardModel* randomCard = robotCards[randomIndex];

      QList<size_t> availableStones;
      for (size_t i = 0; i < STONE_COUNT; i++) {
        if (!m_stones[i].isFull(getPlayer())) {
          availableStones.append(i);
        }
      }
      int availableStonesIndex = generator->bounded(availableStones.size());
      size_t randomStoneIndex = availableStones.at(availableStonesIndex);

      getPlayer().removeCard(randomCard);
      m_stones[randomStoneIndex].addCard(getPlayer(), randomCard);
    }
    if (!getDeck().isEmpty()) {
      getPlayer().pickCard(getDeck().draw());
    }
    GameModel::nextTurn();
  }
}
