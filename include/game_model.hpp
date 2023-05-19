#pragma once

#include <QObject>
#include <QString>

#include "stone_model.hpp"
#include "deck_model.hpp"
#include "player_model.hpp"

#define STONE_COUNT 9

class GameModel : public QObject {
  Q_OBJECT
  Q_PROPERTY(size_t turn READ turn WRITE turnChanged NOTIFY turnChanged)
 public:
  GameModel() {
    for (int i = 0; i < STONE_COUNT; i ++) {
      stones.append(new StoneModel());
    }
    deck = new DeckModel();
    player1 = new PlayerModel();
    player2 = new PlayerModel();
    for (int cardsDrawn = 0; cardsDrawn < 6; cardsDrawn ++) {
      player1->getCards().append(deck->draw());
      player2->getCards().append(deck->draw());
    }
  };
  void setTurn(size_t turn) {
    m_turn = turn;
    emit turnChanged(turn);
  }
  size_t turn() const { return m_turn; };
  QList<StoneModel*> getStones() const { return stones; };
 signals:
  void turnChanged(size_t);

 private:
  size_t m_turn = 0;
  QList<StoneModel *> stones;
  DeckModel* deck;
  PlayerModel* player1;
  PlayerModel* player2;
};
