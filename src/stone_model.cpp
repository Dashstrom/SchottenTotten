/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "stone_model.hpp"

#include <QList>

#include "card_model.hpp"
#include "player_model.hpp"
#include "rule.hpp"
#include "rule_color.hpp"
#include "rule_run.hpp"
#include "rule_same.hpp"

StoneModel::StoneModel() {
  m_rules.append(new RuleColorRun());
  m_rules.append(new RuleColor());
  m_rules.append(new RuleRun());
  m_rules.append(new RuleSame());
}

void StoneModel::addCard(PlayerModel *player, CardModel *card) {
  if (m_firstPlayerId == -1) {
    m_firstPlayerId = player->id();
  }
  m_formations[player->id()].append(card);
}

bool StoneModel::claimable(PlayerModel *player) {
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

bool StoneModel::claims(PlayerModel *player) {
  if (isClaimed()) return false;
  if (claimable(player)) {
    m_claimed = player->id();
    return true;
  }
  return false;
}
