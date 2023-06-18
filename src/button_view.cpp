/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "button_view.hpp"

#include <QLabel>
#include <QString>
#include <QWidget>

#include "image_manager.hpp"

void ButtonView::resizeImage() {
  setPixmap(
      ImageManager::getImageAtSize(m_path, width(), height(), m_keepRatio));
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
  resizeImage();
}
