/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_GAME_MODEL_HPP_
#define INCLUDE_GAME_MODEL_HPP_

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
  GameModel();

  void setTurn(size_t turn);

  void nextTurn();
  bool isEnd() { return isWinner(getPlayer()) || isWinner(getEnemy()); }

  bool isWinner(PlayerModel* player);

  size_t turn() const { return m_turn; }

  QList<StoneModel*> getStones() const { return stones; }

  DeckModel* getDeck() const { return deck; }

  PlayerModel* getPlayer() const { return players[m_turn & 1]; }

  PlayerModel* getEnemy() const { return players[(m_turn + 1) & 1]; }

  void setRobot(PlayerModel* robot);
 signals:
  void turnChanged(size_t);

 private:
  size_t m_turn = 0;
  QList<StoneModel*> stones;
  DeckModel* deck;
  PlayerModel* players[2];
};

#endif  // INCLUDE_GAME_MODEL_HPP_
