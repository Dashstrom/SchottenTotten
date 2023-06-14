/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once

#include <QList>
#include <QObject>
#include <stdexcept>

#include "clan_card_model.hpp"
#include "deck_model.hpp"
class GameModel;

class PlayerModel : public QObject {
  Q_OBJECT

 public:
  explicit PlayerModel(int playerId) { m_playerId = playerId; }

  void removeCard(CardModel *card) {
    if (!m_cards.removeOne(card)) throw 1;
    emit changedCards(m_cards);
  }

  void pickCard(CardModel *card) {
    m_cards.append(card);
    emit changedCards(m_cards);
  }

  int id() const { return m_playerId; }

  int enemyId() const { return (m_playerId + 1) & 1; }

  const QList<CardModel *> getCards() const { return m_cards; }

 signals:
  void changedCards(const QList<CardModel *>);

 private:
  QList<CardModel *> m_cards;
  int m_playerId;
};
