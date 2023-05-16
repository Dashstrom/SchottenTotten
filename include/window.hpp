#pragma once

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
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
