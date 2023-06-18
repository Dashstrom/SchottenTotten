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
#include "stone_model.hpp"

#define STONE_COUNT 9

class GameModel : public QObject {
  Q_OBJECT

 public:
  GameModel();
  virtual ~GameModel();
  virtual void nextTurn();
  bool isEnd() { return isWinner(getPlayer()) || isWinner(getEnemy()); }
  bool isWinner(PlayerModel& player);
  size_t getWinnerId();
  size_t turn() const { return m_turn; }
  StoneModel* getStones() { return stones; }
  DeckModel& getDeck() { return deck; }
  PlayerModel& getPlayer() { return players[m_turn & 1]; }
  PlayerModel& getEnemy() { return players[(m_turn + 1) & 1]; }

 protected:
  size_t m_turn = 0;
  StoneModel stones[STONE_COUNT];
  DeckModel deck;
  PlayerModel players[2];
  QList<CardModel*> cards;
};

#endif  // INCLUDE_GAME_MODEL_HPP_
