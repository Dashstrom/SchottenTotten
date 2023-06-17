/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_FORMATION_VIEW_HPP_
#define INCLUDE_FORMATION_VIEW_HPP_

#include <QGuiApplication>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPixmap>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <Qt>
#include <cmath>

#include "card_layout.hpp"
#include "card_model.hpp"
#include "card_view.hpp"

class FormationView : public QWidget {
  Q_OBJECT

  CardLayout* layout;

 public:
  explicit FormationView(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new CardLayout(20, 90 * M_PI / 180, this);
  }

  void setCards(QList<CardModel*> cards) {
    qDeleteAll(findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
    for (CardModel* cardModel : cards) {
      CardView* cardView = new CardView(cardModel, this);
      layout->addWidget(cardView);
    }
  }

 signals:
  void clicked();

 protected:
  void mousePressEvent(QMouseEvent* event) override {
    // Call the base class implementation
    QWidget::mousePressEvent(event);

    // Emit the custom clicked signal
    emit clicked();
  }
};

#endif  // INCLUDE_FORMATION_VIEW_HPP_
