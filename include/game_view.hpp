/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_GAME_VIEW_HPP_
#define INCLUDE_GAME_VIEW_HPP_

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
  void handleStoneAction(StoneModel& m_stone,
                         StoneView::StoneActionType action);
  void syncPlayer();

 protected:
  void paintEvent(QPaintEvent* e) override;

 private:
  QGridLayout* m_layout;
  QHBoxLayout* m_layoutStones;
  QWidget* m_widgetStones;
  QHBoxLayout* m_layoutHand;
  QWidget* m_widgetHand;
  QHBoxLayout* m_layoutEnemyHand;
  QWidget* m_widgetEnemyHand;
  QLabel* m_playerTurnLabel;
  QLabel* m_deckCountLabel;
  CardView* m_cardViewSelected;
  GameModel* m_game;
  ButtonView* m_buttonFriend;
  ButtonView* m_buttonComputer;
  ButtonView* m_buttonTransition;
  bool m_againstRobot;
  void syncHand(const QList<CardModel*> cards);
  void syncEnemyHand(const QList<CardModel*> cards);
};

#endif  // INCLUDE_GAME_VIEW_HPP_
