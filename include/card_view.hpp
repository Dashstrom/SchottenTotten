/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_CARD_VIEW_HPP_
#define INCLUDE_CARD_VIEW_HPP_

#include <QGraphicsDropShadowEffect>
#include <QGuiApplication>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPixmap>
#include <QRect>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "button_view.hpp"
#include "card_model.hpp"

class CardView : public ButtonView {
  Q_OBJECT

 public:
  CardModel* card;
  QPixmap* image;

  explicit CardView(CardModel* model, QWidget* parent = nullptr)
      : ButtonView("resources/cards/" + model->name(), parent) {
    qDebug() << "Creating CardView";
    card = model;
  }

  void setSelected(bool selected) {
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

  CardModel* getCard() const { return card; }
};

#endif  // INCLUDE_CARD_VIEW_HPP_
