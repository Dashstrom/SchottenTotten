/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "player_robot_model.hpp"

#include <QList>
#include <QRandomGenerator>

#include "stone_model.hpp"

void PlayerRobotModel::playTurn(QList<StoneModel*> stones) {
  QList<CardModel*> robotCards = getCards();
  QRandomGenerator* generator = QRandomGenerator::global();
  if (robotCards.size() != 0) {
    int randomIndex = generator->bounded(robotCards.size());
    CardModel* randomCard = robotCards[randomIndex];

    QList<StoneModel*> availableStones;
    for (StoneModel* stoneModel : stones) {
      if (!stoneModel->isFull(this)) {
        availableStones.append(stoneModel);
      }
    }
    int randomStoneIndex = generator->bounded(availableStones.size());
    StoneModel* randomStone = availableStones[randomStoneIndex];

    removeCard(randomCard);
    randomStone->addCard(this, randomCard);
  }
}
