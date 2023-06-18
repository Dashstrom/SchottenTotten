/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_FORMATION_VIEW_HPP_
#define INCLUDE_FORMATION_VIEW_HPP_

#include <QObject>
#include <QWidget>

#include "card_layout.hpp"
#include "card_model.hpp"
#include "card_view.hpp"

class FormationView : public QWidget {
  Q_OBJECT

 public:
  explicit FormationView(QWidget* parent = nullptr);
  void setCards(QList<CardModel*> cards);

  CardLayout* m_layout;

 signals:
  void clicked();

 protected:
  void mousePressEvent(QMouseEvent* event) override;
};

#endif  // INCLUDE_FORMATION_VIEW_HPP_
