/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "button_view.hpp"

ButtonView::ButtonView(QString path, QWidget* parent) : QLabel(parent) {
  qDebug() << "Loading" << path;
  image = new QPixmap(path);
  resize();
}

void ButtonView::resize() {
  setPixmap(image->scaled(width(), height(), Qt::KeepAspectRatio));
}

void ButtonView::mousePressEvent(QMouseEvent* event) {
  // Call the base class implementation
  QLabel::mousePressEvent(event);

  // Emit the custom clicked signal
  emit clicked();
}

void ButtonView::resizeEvent(QResizeEvent* event) {
  // Call the base class implementation
  QLabel::resizeEvent(event);
  // set a scaled pixmap to a w x h window keeping its aspect ratio
  resize();
}
