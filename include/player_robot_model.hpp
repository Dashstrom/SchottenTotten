/*
Copyright 2023
Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
*/
#pragma once
#include <QRandomGenerator>

#include "player_model.hpp"
#include "stone_model.hpp"

class PlayerRobotModel : public PlayerModel {
  Q_OBJECT

 public:
  explicit PlayerRobotModel(int playerId) : PlayerModel(playerId) {}

  void playTurn(QList<StoneModel*> stones) {
    QList<CardModel*> robotCards = getCards();
    QRandomGenerator* generator = QRandomGenerator::global();
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
};
