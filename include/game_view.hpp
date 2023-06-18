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
#include <QLineEdit>
#include <QMessageBox>
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
 public:
  explicit GameView(QWidget* parent = nullptr);
  void playAgain();
  void transition();
  void clearBoard();
  void setFinalScreen(size_t playerId);
  void handleButton1Clicked();
  void handleButton2Clicked();
  void handleStoneAction(StoneModel* stone, StoneView::StoneActionType action);
  void syncPlayer();

 protected:
  void paintEvent(QPaintEvent* e) override;

 private:
  QGridLayout* layout;
  QHBoxLayout* layoutStones;
  QWidget* widgetStones;
  QHBoxLayout* layoutHand;
  QWidget* widgetHand;
  QHBoxLayout* layoutEnemyHand;
  QWidget* widgetEnemyHand;
  QLabel* playerTurnLabel;
  QLabel* deckCountLabel;
  CardView* cardViewSelected;
  GameModel* game;
  ButtonView* buttonFriend;
  ButtonView* buttonComputer;
  ButtonView* buttonTransition;
  void syncHand(const QList<CardModel*> cards);
  void syncEnemyHand(const QList<CardModel*> cards);
};

#endif  // INCLUDE_GAME_VIEW_HPP_
