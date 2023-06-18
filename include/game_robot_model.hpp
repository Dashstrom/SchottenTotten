/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_GAME_ROBOT_MODEL_HPP_
#define INCLUDE_GAME_ROBOT_MODEL_HPP_

#include <QObject>

#include "game_model.hpp"

class GameRobotModel : public GameModel {
  Q_OBJECT

  void nextTurn() override;
};

#endif  // INCLUDE_GAME_ROBOT_MODEL_HPP_
