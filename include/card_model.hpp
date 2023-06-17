/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_CARD_MODEL_HPP_
#define INCLUDE_CARD_MODEL_HPP_

#include <QObject>
#include <QString>

class CardModel : public QObject {
  Q_OBJECT

 public:
  enum CardColor { Green, Blue, Red, Yellow, Purple, Brown };
  Q_ENUM(CardColor);
  virtual QString name() const = 0;
  virtual int strength() const = 0;
  virtual CardColor color() const = 0;
};

#endif  // INCLUDE_CARD_MODEL_HPP_
