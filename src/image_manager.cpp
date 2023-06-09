/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "image_manager.hpp"

#include <QDebug>
#include <QPixmap>
#include <QPixmapCache>
#include <QString>

QPixmap ImageManager::getImage(QString path) {
  QPixmap image;
  if (!QPixmapCache::find(path, &image)) {
    qDebug() << "Loading" << path;
    image = QPixmap(path);
    QPixmapCache::insert(path, image);
  } else {
    qDebug() << "Loading from cache" << path;
  }
  return image;
}

QPixmap ImageManager::getImageAtSize(QString path, int width, int height,
                                     bool keepRatio) {
  QString key = path + ";" + QString::number(width) + ";" +
                QString::number(height) + ";" + QString::number(keepRatio);
  QPixmap image;
  if (!QPixmapCache::find(key, &image)) {
    image = getImage(path).scaled(
        width, height, keepRatio ? Qt::KeepAspectRatio : Qt::IgnoreAspectRatio);
    QPixmapCache::insert(key, image);
  }
  return image;
}
