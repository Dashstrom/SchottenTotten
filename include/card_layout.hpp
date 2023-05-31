/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
   insired from https://doc.qt.io/qt-6/layout.html
 */
#pragma once

#include <QList>
#include <QtWidgets>
#include <cmath>

class CardLayout : public QLayout {
 public:
  CardLayout(int spacing, double radians = 45 * M_PI / 180,
             QWidget *parent = nullptr)
      : QLayout(parent), m_radians(radians) {
    setSpacing(spacing);
  }
  ~CardLayout();

  void addItem(QLayoutItem *item) override;
  QSize sizeHint() const override;
  QSize minimumSize() const override;
  int count() const override;
  QLayoutItem *itemAt(int) const override;
  QLayoutItem *takeAt(int) override;
  void setGeometry(const QRect &rect) override;
  double spacingX() const { return spacing() * cos(m_radians); }
  double spacingY() const { return spacing() * sin(m_radians); }

 private:
  QList<QLayoutItem *> m_items;
  double m_radians;
};
