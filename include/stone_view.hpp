/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_STONE_VIEW_HPP_
#define INCLUDE_STONE_VIEW_HPP_

#include <QGridLayout>
#include <QObject>
#include <QWidget>

#include "button_view.hpp"
#include "card_model.hpp"
#include "card_view.hpp"
#include "formation_view.hpp"
#include "player_model.hpp"
#include "stone_model.hpp"

class StoneView : public QWidget {
  Q_OBJECT

  FormationView* formationView1;
  FormationView* formationView2;
  QGridLayout* layout;
  ButtonView* stoneButtonTop;
  ButtonView* stoneButton;
  ButtonView* stoneButtonBot;
  StoneModel* stone;
  int m_skin;

 public:
  enum StoneActionType { Formation1, Formation2, Stone };
  Q_ENUM(StoneActionType)
  explicit StoneView(StoneModel* model, PlayerModel* player, PlayerModel* enemy,
                     int skin, QWidget* parent = nullptr);
  StoneModel* getStone() { return stone; }

 signals:
  void action(StoneActionType actionType);
};

#endif  // INCLUDE_STONE_VIEW_HPP_
