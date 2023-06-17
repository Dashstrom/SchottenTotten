/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_BUTTON_VIEW_HPP_
#define INCLUDE_BUTTON_VIEW_HPP_

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

#include "card_model.hpp"

class ButtonView : public QLabel {
  Q_OBJECT

 public:
  QPixmap* image;

  explicit ButtonView(QString path, QWidget* parent = nullptr);

  void resize();

 signals:
  void clicked();

 protected:
  void mousePressEvent(QMouseEvent* event) override;

  void resizeEvent(QResizeEvent* event) override;
};
#endif  // INCLUDE_BUTTON_VIEW_HPP_
