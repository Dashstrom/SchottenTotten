/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once

#include <QObject>
#include <QString>

#include "deck_model.hpp"
#include "player_model.hpp"
#include "player_robot_model.hpp"
#include "stone_model.hpp"

#define STONE_COUNT 9

class GameModel : public QObject {
  Q_OBJECT
  Q_PROPERTY(size_t turn READ turn WRITE turnChanged NOTIFY turnChanged)

 public:
  GameModel() {
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

  void setTurn(size_t turn) {
    m_turn = turn;
    emit turnChanged(turn);
  }

  void nextTurn() {
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

  bool isEnd() {
    return isWinner(getPlayer()) || isWinner(getEnemy()) ||
           (getPlayer()->getCards().size() == 0 &&
            getEnemy()->getCards().size() == 0);
  }

  bool isWinner(PlayerModel* player) {
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

  size_t getWinnerId() {
    int claimedPlayer = 0;
    int claimedAdjacentPlayer = 0;
    int claimedEnemy = 0;
    int claimedAdjacentEnemy = 0;
    // Player1
    for (StoneModel* stone : stones) {
      if (stone->isClaimedBy(getPlayer())) {
        claimedPlayer += 1;
        claimedAdjacentPlayer += 1;
      } else {
        claimedAdjacentPlayer = 0;
      }
    }

    // Player2
    for (StoneModel* stone : stones) {
      if (stone->isClaimedBy(getEnemy())) {
        claimedEnemy += 1;
        claimedAdjacentEnemy += 1;
      } else {
        claimedAdjacentEnemy = 0;
      }
    }

    if ((claimedPlayer > claimedEnemy) ||
        (claimedAdjacentPlayer > claimedAdjacentEnemy)) {
      return getPlayer()->id();
    } else if ((claimedPlayer < claimedEnemy) ||
               (claimedAdjacentPlayer < claimedAdjacentEnemy)) {
      return getEnemy()->id();
    } else {
      return -1;
    }
  }

  size_t turn() const { return m_turn; }

  QList<StoneModel*> getStones() const { return stones; }

  DeckModel* getDeck() const { return deck; }

  PlayerModel* getPlayer() const { return players[m_turn & 1]; }

  PlayerModel* getEnemy() const { return players[(m_turn + 1) & 1]; }

  void setRobot(PlayerModel* robot) {
    QList<CardModel*> cards = players[1]->getCards();
    for (CardModel* card : cards) {
      robot->pickCard(card);
    }
    players[1] = robot;
  }
 signals:
  void turnChanged(size_t);

 private:
  size_t m_turn = 0;
  QList<StoneModel*> stones;
  DeckModel* deck;
  PlayerModel* players[2];
};
