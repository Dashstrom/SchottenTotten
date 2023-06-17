/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "card_view.hpp"

CardView::CardView(CardModel* model, QWidget* parent)
    : ButtonView("resources/cards/" + model->name(), parent) {
  qDebug() << "Creating CardView";
  card = model;
}

void CardView::setSelected(bool selected) {
  if (selected) {
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(5);
    effect->setXOffset(5);
    effect->setYOffset(5);
    effect->setColor(Qt::black);
    this->setGraphicsEffect(effect);
  } else {
    this->setGraphicsEffect(nullptr);
  }
}
