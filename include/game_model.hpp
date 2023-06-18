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
  StoneModel* getStones() { return m_stones; }
  DeckModel& getDeck() { return m_deck; }
  PlayerModel& getPlayer() { return m_players[m_turn & 1]; }
  PlayerModel& getEnemy() { return m_players[(m_turn + 1) & 1]; }

 protected:
  size_t m_turn = 0;
  StoneModel m_stones[STONE_COUNT];
  DeckModel m_deck;
  PlayerModel m_players[2];
  QList<CardModel*> m_cards;
};

#endif  // INCLUDE_GAME_MODEL_HPP_
