/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "stone_view.hpp"

#include <QDebug>
#include <QGridLayout>
#include <QWidget>

#include "button_view.hpp"
#include "formation_view.hpp"
#include "player_model.hpp"
#include "stone_model.hpp"

StoneView::StoneView(StoneModel& model, PlayerModel& player, PlayerModel& enemy,
                     size_t skin, QWidget* parent)
    : QWidget(parent), m_skin(skin), m_stone(model) {
  qDebug() << "Creating stone view";

  m_layout = new QGridLayout(this);
  m_layout->setContentsMargins(0, 0, 0, 0);
  m_layout->setSpacing(0);

  m_formationView1 = new FormationView(this);
  m_formationView1->setCards(m_stone.getCards(player));
  m_formationView2 = new FormationView(this);
  m_formationView2->setCards(m_stone.getCards(enemy));

  QString stonePath("resources/stones/" + QString::number(m_skin % 9) +
                    "_.jpg");
  QString emptyPath("resources/stones/empty.png");

  // compute responsive dimensions
  if (m_stone.isClaimed()) {
    m_stoneButton = new ButtonView(emptyPath, this);
    if (m_stone.isClaimedBy(player)) {
      m_stoneButtonTop = new ButtonView(emptyPath, this);
      m_stoneButtonBot = new ButtonView(stonePath, this);
    } else {
      m_stoneButtonTop = new ButtonView(stonePath, this);
      m_stoneButtonBot = new ButtonView(emptyPath, this);
    }
  } else {
    m_stoneButton = new ButtonView(stonePath, this);
    m_stoneButtonTop = new ButtonView(emptyPath, this);
    m_stoneButtonBot = new ButtonView(emptyPath, this);
  }

  m_layout->addWidget(m_stoneButtonTop, 0, 0);
  m_layout->addWidget(m_formationView2, 1, 0);
  m_layout->addWidget(m_stoneButton, 2, 0);
  m_layout->addWidget(m_formationView1, 3, 0);
  m_layout->addWidget(m_stoneButtonBot, 4, 0);

  // define the relative proportions of the rows
  m_layout->setRowStretch(0, 60);
  m_layout->setRowStretch(1, 100);
  m_layout->setRowStretch(2, 60);
  m_layout->setRowStretch(3, 100);
  m_layout->setRowStretch(4, 60);

  connect(&m_stone, &StoneModel::changed, this, [this, &player, &enemy] {
    this->m_formationView1->setCards(this->m_stone.getCards(player));
    this->m_formationView2->setCards(this->m_stone.getCards(enemy));
  });

  connect(m_formationView1, &FormationView::clicked, this,
          [&] { emit action(StoneView::Formation1); });
  connect(m_stoneButton, &ButtonView::clicked, this,
          [&] { emit action(StoneView::Stone); });
  connect(m_formationView2, &FormationView::clicked, this,
          [&] { emit action(StoneView::Formation2); });
}
