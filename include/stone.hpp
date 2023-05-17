#pragma once

#include <QGuiApplication>
#include <QLabel>
#include <QPixmap>
#include <QScreen>
#include <QVBoxLayout>

class Stone : public QWidget {
  Q_OBJECT

public:
  Stone(QWidget *parent = nullptr);

  QLabel *getStoneMain() const { return stoneMain; }
  QVBoxLayout *getLayoutFormation1() { return layoutFormation1; }
  QVBoxLayout *getLayoutFormation2() { return layoutFormation2; }

signals:
  void clicked(Stone *stone);

protected:
  void mousePressEvent(QMouseEvent *event) override {
    // Emit the custom clicked signal
    emit clicked(this);

    // Call the base class implementation
    QWidget::mousePressEvent(event);
  }

  // private slots:
  //   void onClicked() {
  //     qDebug() << "onClicked";
  //     // Handle the click event
  //     // ...

  //     // stoneMain->setStyleSheet("border: 2px solid red;");
  //   }

private:
  QVBoxLayout *layoutFormation1;
  QLabel *stoneMain;
  QVBoxLayout *layoutFormation2;
};
