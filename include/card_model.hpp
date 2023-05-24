/*
Copyright 2023
Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
*/
#pragma once

#include <QObject>
#include <QString>

class CardModel : public QObject {
  Q_OBJECT

 public:
  virtual QString name() const = 0;
};
