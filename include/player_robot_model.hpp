/*
Copyright 2023
Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
*/
#pragma once

#include <QRandomGenerator>

#include "game_model.hpp"
#include "player_model.hpp"
#include "stone_model.hpp"

class PlayerRobotModel : public PlayerModel {
  Q_OBJECT

 public:
  explicit PlayerRobotModel(int playerId, int level)
      : PlayerModel(playerId), level(level) {}

  void playTurn(GameModel* game) {
    if (level == 1) {
      QList<CardModel*> robotCards = getCards();
      QRandomGenerator* generator = QRandomGenerator::global();
      int randomIndex = generator->bounded(robotCards.size());
      CardModel* randomCard = robotCards[randomIndex];

      QList<StoneModel*> availableStones;
      for (StoneModel* stoneModel : game->getStones()) {
        if (!stoneModel->isFull(this)) {
          availableStones.append(stoneModel);
        }
      }
      int randomStoneIndex = generator->bounded(availableStones.size());
      StoneModel* randomStone = availableStones[randomStoneIndex];

      removeCard(randomCard);
      randomStone->addCard(this, randomCard);

      if (!game->getDeck()->isEmpty()) {
        pickCard(game->getDeck()->draw());
      }

      game->nextTurn();
    } else if (level == 1) {
      // TODO(Soudarsane) replace this code by an other robot comportment
      if (level == 1) {
        QList<CardModel*> robotCards = getCards();
        QRandomGenerator* generator = QRandomGenerator::global();
        int randomIndex = generator->bounded(robotCards.size());
        CardModel* randomCard = robotCards[randomIndex];

        QList<StoneModel*> availableStones;
        for (StoneModel* stoneModel : game->getStones()) {
          if (!stoneModel->isFull(this)) {
            availableStones.append(stoneModel);
          }
        }
        int randomStoneIndex = generator->bounded(availableStones.size());
        StoneModel* randomStone = availableStones[randomStoneIndex];

        removeCard(randomCard);
        randomStone->addCard(this, randomCard);

        if (!game->getDeck()->isEmpty()) {
          pickCard(game->getDeck()->draw());
        }

        game->nextTurn();
      }
    }
  }

 private:
  int level;
};
