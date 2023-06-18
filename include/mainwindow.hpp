/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_MAINWINDOW_HPP_
#define INCLUDE_MAINWINDOW_HPP_

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() = default;
};

#endif  // INCLUDE_MAINWINDOW_HPP_
