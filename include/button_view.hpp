/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once

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
#include "image_manager.hpp"

class ButtonView : public QLabel {
  Q_OBJECT

 public:
  explicit ButtonView(QString path, QWidget* parent = nullptr)
      : QLabel(parent), m_path(path) {
    qDebug() << "Loading" << path;
    image = ImageManager::getImageAtSize(path, width(), height());
    resize();
  }
  void resize() {
    setPixmap(ImageManager::getImageAtSize(m_path, width(), height()));
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
    // set a scaled pixmap to a w x h window keeping its aspect ratio
    resize();
    // Call the base class implementation
    QLabel::resizeEvent(event);
  }

 private:
  QPixmap image;
  QString m_path;
};
