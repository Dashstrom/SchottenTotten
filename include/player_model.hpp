/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_PLAYER_MODEL_HPP_
#define INCLUDE_PLAYER_MODEL_HPP_

#include <QList>
#include <QObject>

#include "clan_card_model.hpp"
#include "deck_model.hpp"

class PlayerModel : public QObject {
  Q_OBJECT

 public:
  explicit PlayerModel(int playerId) { m_playerId = playerId; }

  void removeCard(CardModel *card);

  void pickCard(CardModel *card);

  int id() const { return m_playerId; }

  int enemyId() const { return (m_playerId + 1) & 1; }

  const QList<CardModel *> getCards() const { return m_cards; }

 signals:
  void changedCards(const QList<CardModel *>);

 private:
  QList<CardModel *> m_cards;
  int m_playerId;
};

#endif  // INCLUDE_PLAYER_MODEL_HPP_
