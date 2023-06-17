#include <QPixmap>
#include <QString>
#include <QPixmapCache>


class ImageManager {
  

 public:
  static QPixmap getImage(QString path) {
    QPixmap image;
    if (!QPixmapCache::find(path, &image)) {
      image = QPixmap(path);
      QPixmapCache::insert(path, image);
    }
    return image;
  };
  static QPixmap getImageAtSize(QString path, int width, int height) {
    QString key = path + ";" + QString::number(width) + ";" + QString::number(height);
    QPixmap image;
    if (!QPixmapCache::find(key, &image)) {
      image = getImage(path).scaled(width, height, Qt::KeepAspectRatio);
      QPixmapCache::insert(key, image);
    }
    return image;
    
  };
};
