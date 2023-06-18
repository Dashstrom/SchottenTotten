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
#include <QMouseEvent>
#include <QObject>
#include <QPixmap>
#include <QRect>
#include <QResizeEvent>
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
    resizeImage();
  }

 signals:
  void clicked();

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;

 private:
  QString m_path;
  void resizeImage();
};
#endif  // INCLUDE_BUTTON_VIEW_HPP_
