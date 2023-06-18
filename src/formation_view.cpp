/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "formation_view.hpp"

#include <QMouseEvent>
#include <QWidget>
#include <Qt>
#include <QtAlgorithms>  // qDeleteAll

#include "card_layout.hpp"
#include "card_model.hpp"
#include "card_view.hpp"

FormationView::FormationView(QWidget* parent) : QWidget(parent) {
  layout = new CardLayout(25, 90 * M_PI / 180, this);
}

void FormationView::setCards(QList<CardModel*> cards) {
  qDeleteAll(findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
  for (CardModel* cardModel : cards) {
    CardView* cardView = new CardView(cardModel, this);
    layout->addWidget(cardView);
  }
}

void FormationView::mousePressEvent(QMouseEvent* event) {
  // Call the base class implementation
  QWidget::mousePressEvent(event);

  // Emit the custom clicked signal
  emit clicked();
}
