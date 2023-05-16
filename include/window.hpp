#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QWidget>
#include <iostream>

class MainWindow : public QMainWindow {

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;
};
