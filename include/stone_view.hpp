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

 public:
  enum StoneActionType { Formation1, Formation2, Stone };
  Q_ENUM(StoneActionType)
  explicit StoneView(StoneModel& model, PlayerModel& player, PlayerModel& enemy,
                     size_t skin, QWidget* parent = nullptr);
  StoneModel& getStone() { return m_stone; }

 signals:
  void action(StoneActionType actionType);

 private:
  FormationView* m_formationView1;
  FormationView* m_formationView2;
  QGridLayout* m_layout;
  ButtonView* m_stoneButtonTop;
  ButtonView* m_stoneButton;
  ButtonView* m_stoneButtonBot;
  StoneModel& m_stone;
  size_t m_skin;
};

#endif  // INCLUDE_STONE_VIEW_HPP_
