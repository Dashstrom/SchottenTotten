/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_CARD_VIEW_HPP_
#define INCLUDE_CARD_VIEW_HPP_

#include <QObject>
#include <QPixmap>
#include <QWidget>

#include "button_view.hpp"
#include "card_model.hpp"

class CardView : public ButtonView {
  Q_OBJECT

 public:
  CardModel* m_card;
  QPixmap* m_image;

  explicit CardView(CardModel* model, QWidget* parent = nullptr);
  void setSelected(bool selected);
  CardModel* getCard() const { return m_card; }
};

#endif  // INCLUDE_CARD_VIEW_HPP_
