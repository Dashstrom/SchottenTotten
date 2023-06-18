/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_IMAGE_MANAGER_HPP_
#define INCLUDE_IMAGE_MANAGER_HPP_

#include <QPixmap>
#include <QString>

class ImageManager {
 public:
  static QPixmap getImage(QString path);
  static QPixmap getImageAtSize(QString path, int width, int height,
                                bool keepRatio);
};

#endif  // INCLUDE_IMAGE_MANAGER_HPP_
