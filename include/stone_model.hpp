/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_STONE_MODEL_HPP_
#define INCLUDE_STONE_MODEL_HPP_

#include <QList>
#include <QObject>

class PlayerModel;

#include "card_model.hpp"
#include "player_model.hpp"
#include "rule.hpp"
#include "rule_color.hpp"
#include "rule_color_run.hpp"
#include "rule_run.hpp"
#include "rule_same.hpp"

class StoneModel : public QObject {
  Q_OBJECT

 public:
  StoneModel();
  ~StoneModel() {
    for (Rule* rule : m_rules) {
      delete rule;
    }
  }

  const QList<CardModel*> getCards(PlayerModel& player) const {
    return m_formations[player.id()];
  }

  void addCard(PlayerModel& player, CardModel* card);

  void removeCard(PlayerModel& player, CardModel* card) {
    m_formations[player.id()].removeOne(card);
  }

  bool isFull(PlayerModel& player) const {
    return getCards(player).count() >= m_size;
  }

  bool claimable(PlayerModel& player);

  bool claims(PlayerModel& player);

  int isClaimedBy(PlayerModel& player) const {
    return m_claimed == player.id();
  }

  int isClaimed() const { return m_claimed != -1; }

  void addSize(int size) { m_size += size; }

 signals:
  void changed();

 private:
  QList<CardModel*> m_formations[2];
  QList<Rule*> m_rules;
  int m_firstPlayerId = -1;
  int m_size = 3;
  int m_claimed = -1;
};

#endif  // INCLUDE_STONE_MODEL_HPP_
