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
  explicit FormationView(QWidget* parent = nullptr);

  void setCards(QList<CardModel*> cards);

 signals:
  void clicked();

 protected:
  void mousePressEvent(QMouseEvent* event) override;
};

#endif  // INCLUDE_FORMATION_VIEW_HPP_
