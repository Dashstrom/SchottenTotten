/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_STONE_VIEW_HPP_
#define INCLUDE_STONE_VIEW_HPP_

#include <QGridLayout>
#include <QGuiApplication>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QString>
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

 public:
  enum StoneActionType { Formation1, Formation2, Stone };
  Q_ENUM(StoneActionType)
  explicit StoneView(StoneModel* model, PlayerModel* player, PlayerModel* enemy,
                     QWidget* parent = nullptr)
      : QWidget(parent) {
    qDebug() << "Creating stone view";
    stone = model;

    layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    formationView1 = new FormationView(this);
    formationView1->setCards(stone->getCards(player));
    formationView2 = new FormationView(this);
    formationView2->setCards(stone->getCards(enemy));

    // compute responsive dimensions
    // TODO(Marin Bouanchaud): make it responsive with window resize

    if (stone->isClaimed()) {
      stoneButton = new ButtonView("resources/stone-empty.png", this);
      if (stone->isClaimedBy(player)) {
        stoneButtonTop = new ButtonView("resources/stone-empty.png", this);
        stoneButtonBot = new ButtonView("resources/stone.png", this);
      } else {
        stoneButtonTop = new ButtonView("resources/stone.png", this);
        stoneButtonBot = new ButtonView("resources/stone-empty.png", this);
      }
    } else {
      stoneButton = new ButtonView("resources/stone.png", this);
      stoneButtonTop = new ButtonView("resources/stone-empty.png", this);
      stoneButtonBot = new ButtonView("resources/stone-empty.png", this);
    }

    layout->addWidget(stoneButtonTop, 0, 0);
    layout->addWidget(formationView2, 1, 0);
    layout->addWidget(stoneButton, 2, 0);
    layout->addWidget(formationView1, 3, 0);
    layout->addWidget(stoneButtonBot, 4, 0);

    // define the relative proportions of the rows
    layout->setRowStretch(0, 60);
    layout->setRowStretch(1, 100);
    layout->setRowStretch(2, 60);
    layout->setRowStretch(3, 100);
    layout->setRowStretch(4, 60);

    connect(stone, &StoneModel::changed, this, [this, player, enemy] {
      this->formationView1->setCards(this->stone->getCards(player));
      this->formationView2->setCards(this->stone->getCards(enemy));
    });

    connect(formationView1, &FormationView::clicked, this,
            [&] { emit action(StoneView::Formation1); });
    connect(stoneButton, &ButtonView::clicked, this,
            [&] { emit action(StoneView::Stone); });
    connect(formationView2, &FormationView::clicked, this,
            [&] { emit action(StoneView::Formation2); });
  }
  StoneModel* getStone() { return stone; }

 signals:
  void action(StoneActionType actionType);
};

#endif  // INCLUDE_STONE_VIEW_HPP_
