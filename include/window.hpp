#pragma once

#include <QAction>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPixmap>
#include <iostream>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);

private slots:
  void onRestartActionTriggered();
  void onQuitActionTriggered();

private:
  QMenuBar *menuBar;
  QMenu *gameMenu;
};