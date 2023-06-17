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

  explicit ButtonView(QString path, QWidget* parent = nullptr)
      : QLabel(parent) {
    qDebug() << "Loading" << path;
    image = new QPixmap(path);
    resize();
  }
  void resize() {
    setPixmap(image->scaled(width(), height(), Qt::KeepAspectRatio));
  }

 signals:
  void clicked();

 protected:
  void mousePressEvent(QMouseEvent* event) override {
    // Call the base class implementation
    QLabel::mousePressEvent(event);

    // Emit the custom clicked signal
    emit clicked();
  }

  void resizeEvent(QResizeEvent* event) override {
    // Call the base class implementation
    QLabel::resizeEvent(event);
    // set a scaled pixmap to a w x h window keeping its aspect ratio
    resize();
  }
};

#endif  // INCLUDE_BUTTON_VIEW_HPP_
