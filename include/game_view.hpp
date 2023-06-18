/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_GAME_VIEW_HPP_
#define INCLUDE_GAME_VIEW_HPP_
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPaintEvent>
#include <QWidget>

#include "card_model.hpp"
#include "card_view.hpp"
#include "game_model.hpp"
#include "player_robot_model.hpp"
#include "stone_model.hpp"
#include "stone_view.hpp"

class GameView : public QWidget {
  QGridLayout* layout;

  QHBoxLayout* layoutStones;
  QWidget* widgetStones;

  QHBoxLayout* layoutHand;
  QWidget* widgetHand;

  QHBoxLayout* layoutEnemyHand;
  QWidget* widgetEnemyHand;

  QLabel* playerTurnLabel;
  QLabel* deckCountLabel;

  CardView* cardViewSelected = nullptr;

  GameModel* game;

  ButtonView* buttonFriend;
  ButtonView* buttonComputer;
  int resizeFactor = 100;

 public:
  explicit GameView(GameModel* model, QWidget* parent = nullptr);

  void handleButton1Clicked();

  void handleButton2Clicked();

  void syncPlayer();

  void resize();

 protected:
  void paintEvent(QPaintEvent* e) override;

  void resizeEvent(QResizeEvent* event) override;

 private:
  void syncHand(const QList<CardModel*> cards);

  void syncEnemyHand(const QList<CardModel*> cards);
};

#endif  // INCLUDE_GAME_VIEW_HPP_
