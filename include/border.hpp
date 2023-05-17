#pragma once

#include "stone.hpp"
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QScreen>
#include <QWidget>

class Border : public QLabel {
  Q_OBJECT

public:
  Border(QWidget *parent = nullptr);

private:
  Stone *currentClickedStone;

  void onStoneClicked(Stone *stone);
};
