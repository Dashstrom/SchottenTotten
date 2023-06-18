/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_PLAYER_ROBOT_MODEL_HPP_
#define INCLUDE_PLAYER_ROBOT_MODEL_HPP_

#include <QRandomGenerator>

#include "player_model.hpp"
#include "stone_model.hpp"

class PlayerRobotModel : public PlayerModel {
  Q_OBJECT

 public:
  explicit PlayerRobotModel(int playerId) : PlayerModel(playerId) {}
  void playTurn(QList<StoneModel*> stones);
};

#endif  // INCLUDE_PLAYER_ROBOT_MODEL_HPP_
