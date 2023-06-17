/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once

#include <QGuiApplication>
#include <QLabel>
#include <QList>
#include <QPixmap>
#include <QVBoxLayout>

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
  StoneModel() {
    m_rules.append(new RuleColorRun());
    m_rules.append(new RuleColor());
    m_rules.append(new RuleRun());
    m_rules.append(new RuleSame());
  }
  ~StoneModel() {
    for (Rule *rule : m_rules) {
      delete rule;
    }
  }

  const QList<CardModel *> getCards(PlayerModel *player) const {
    return m_formations[player->id()];
  }

  void addCard(PlayerModel *player, CardModel *card) {
    if (m_firstPlayerId == -1) {
      m_firstPlayerId = player->id();
    }
    m_formations[player->id()].append(card);
  }

  void removeCard(PlayerModel *player, CardModel *card) {
    m_formations[player->id()].removeOne(card);
  }

  bool isFull(PlayerModel *player) const {
    return getCards(player).count() >= m_size;
  }

  bool claimable(PlayerModel *player) {
    QList<CardModel *> playerCards = m_formations[player->id()];
    QList<CardModel *> enemyCards = m_formations[player->enemyId()];

    // TODO(Dashstrom) : predict if stone can't be claim
    if (playerCards.count() != enemyCards.count() ||
        playerCards.count() != m_size)
      return false;
    if (playerCards.count() != enemyCards.count() ||
        playerCards.count() != m_size)
      return false;

    for (Rule *rule : m_rules) {
      bool rulePlayer = rule->match(playerCards);
      bool ruleEnemy = rule->match(enemyCards);
      if (rulePlayer ^ ruleEnemy) {  // rulePlayer xor ruleEnemy
        if (rulePlayer) {            // only work if rule player
          return true;
        }
        break;
      }
    }
    int sumPlayer = 0;
    for (auto card : playerCards) sumPlayer += card->strength();
    int sumEnemy = 0;
    for (auto card : enemyCards) sumEnemy += card->strength();
    if (sumPlayer == sumEnemy) return m_firstPlayerId == player->id();
    return sumPlayer > sumEnemy;
  }

  bool claims(PlayerModel *player) {
    if (isClaimed()) return false;
    if (claimable(player)) {
      m_claimed = player->id();
      return true;
    }
    return false;
  }

  int isClaimedBy(PlayerModel *player) const {
    return m_claimed == player->id();
  }

  int isClaimed() const { return m_claimed != -1; }

  void addSize(int size) { m_size += size; }

 signals:
  void changed();

 private:
  QList<CardModel *> m_formations[2];
  QList<Rule *> m_rules;
  int m_firstPlayerId = -1;
  int m_size = 3;
  int m_claimed = -1;
};
