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

  QPushButton* buttonPlayAgain;
  ButtonView* buttonTransition;
 public:
  void playAgain() {
    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != 0) {
      qDebug() << "Deleting" << child;
      child->widget()->deleteLater();  // delete the widget
      delete child;
    }

    game = new GameModel();

    // Buttons for player choice (friend = button1, robot = button 2)
    buttonFriend = new ButtonView("resources/players/friend.jpg", this);
    buttonComputer = new ButtonView("resources/players/computer.jpg", this);
    QPixmap friendPixmap("resources/players/friend.jpg");
    QPixmap computerPixmap("resources/players/computer.jpg");
    QSize imageSize = friendPixmap.size().boundedTo(computerPixmap.size());
    buttonFriend->setFixedSize(imageSize);
    buttonComputer->setFixedSize(imageSize);
    qDebug() << "Play Again :";

    layout->addWidget(buttonFriend, 1, 0);
    layout->addWidget(buttonComputer, 1, 1);

    // connexion of buttons
    connect(buttonFriend, &ButtonView::clicked, this,
            [this]() { handleButton1Clicked(); });

    connect(buttonComputer, &ButtonView::clicked, this,
            [this]() { handleButton2Clicked(); });
  }

  // Display who's turn to play
  void transition() {
    if (!game->againstRobot()) {
      QLayoutItem* child;
      while ((child = layout->takeAt(0)) != 0) {
        qDebug() << "Deleting" << child;
        child->widget()->deleteLater();  // delete the widget
        delete child;
      }

      if (game->turn() % 2 == 0) {
        buttonTransition = new ButtonView("resources/players/player1Turn.png");
      } else {
        buttonTransition = new ButtonView("resources/players/player2Turn.png");
      }

      layout->addWidget(buttonTransition, 1, 0);

      connect(buttonTransition, &ButtonView::clicked, this,
              [this]() { syncPlayer(); });
    } else {
      syncPlayer();
    }
  }

  void setFinalScreen(size_t playerId) {
    // Création d'une nouvelle fenêtre
    QMainWindow* newWindow = new QMainWindow();

    buttonPlayAgain = new QPushButton(this);

    if (playerId == 0) {
      QPixmap buttonImageFriend("resources/players/player1Wins.png");
      buttonPlayAgain->setIcon(buttonImageFriend);
      buttonPlayAgain->setIconSize(buttonImageFriend.size());
    } else if (playerId == 1) {
      if (game->againstRobot()) {
        QPixmap buttonImageFriend("resources/players/robotWins.png");
        buttonPlayAgain->setIcon(buttonImageFriend);
        buttonPlayAgain->setIconSize(buttonImageFriend.size());
      } else {
        QPixmap buttonImageFriend("resources/players/player2Wins.png");
        buttonPlayAgain->setIcon(buttonImageFriend);
        buttonPlayAgain->setIconSize(buttonImageFriend.size());
      }
    } else {
      QPixmap buttonImageFriend("resources/players/noOneWon.png");
      buttonPlayAgain->setIcon(buttonImageFriend);
      buttonPlayAgain->setIconSize(buttonImageFriend.size());
    }
    connect(buttonPlayAgain, &QPushButton::clicked, this, [this, newWindow]() {
      newWindow->close();
      playAgain();
    });

    newWindow->setCentralWidget(buttonPlayAgain);
    newWindow->show();
  }

  bool reorganizeEndGame() {
    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != 0) {
      qDebug() << "Deleting" << child;
      child->widget()->deleteLater();  // delete the widget
      delete child;
    }
    qDebug() << "Create child";
    widgetStones = new QWidget(this);
    layoutStones = new QHBoxLayout(widgetStones);
    layoutStones->setContentsMargins(0, 0, 0, 0);
    layoutStones->setSpacing(10);

    widgetHand = new QWidget(this);
    layoutHand = new QHBoxLayout(widgetHand);

    widgetEnemyHand = new QWidget(this);
    layoutEnemyHand = new QHBoxLayout(widgetEnemyHand);

    layout->addWidget(widgetEnemyHand, 0, 0);
    layout->addWidget(widgetStones, 1, 0);
    layout->addWidget(widgetHand, 2, 0);

    // define the relative proportions of the rows
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 3);
    layout->setRowStretch(2, 1);
    for (StoneModel* stoneModel : game->getStones()) {
      StoneView* stone = new StoneView(stoneModel, game->getPlayer(),
                                       game->getEnemy(), widgetStones);
      layoutStones->addWidget(stone);
    }
    return true;
  }

  explicit GameView(GameModel* model, QWidget* parent = nullptr);
  void handleButton1Clicked();
  void handleButton2Clicked();
  void syncPlayer();


 protected:
  void paintEvent(QPaintEvent* e) override;

 private:
  void syncHand(const QList<CardModel*> cards);
  void syncEnemyHand(const QList<CardModel*> cards);
};

#endif  // INCLUDE_GAME_VIEW_HPP_
