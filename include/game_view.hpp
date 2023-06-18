/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QPushButton>
#include <QRandomGenerator>
#include <QSizePolicy>
#include <QString>
#include <QVBoxLayout>
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

  QPushButton* buttonFriend;
  QPushButton* buttonComputer;

  QPushButton* buttonPlayAgain;
  QPushButton* buttonTransition;

  // int resizeFactor = 100;
  // QMainWindow* parentWindow;
 public:
  explicit GameView(GameModel* model, QWidget* parent = nullptr)
      : QWidget(parent) {
    qDebug() << "Creating game view";
    game = model;
    layout = new QGridLayout(this);

    // Buttons for player choice (friend = button1, robot = button 2)
    buttonFriend = new QPushButton(this);
    buttonComputer = new QPushButton(this);
    QPixmap buttonImageFriend("resources/players/friend.jpg");
    QPixmap buttonImageComputer("resources/players/computer.jpg");
    buttonFriend->setIcon(buttonImageFriend);
    buttonFriend->setIconSize(buttonImageFriend.size());
    buttonComputer->setIcon(buttonImageComputer);
    buttonComputer->setIconSize(buttonImageComputer.size());

    layout->addWidget(buttonFriend, 0, 0);
    layout->addWidget(buttonComputer, 0, 1);

    // connexion of buttons
    connect(buttonFriend, &QPushButton::clicked, this,
            [this]() { handleButton1Clicked(); });

    connect(buttonComputer, &QPushButton::clicked, this,
            [this]() { handleButton2Clicked(); });
  }

  void handleButton1Clicked() {
    buttonFriend->hide();
    buttonComputer->hide();
    transition();
    connect(game, &GameModel::turnChanged, this, &GameView::transition);
  }
  void handleButton2Clicked() {
    buttonFriend->hide();
    buttonComputer->hide();
    PlayerRobotModel* robot = new PlayerRobotModel(1);

    game->setRobot(robot);
    transition();
    connect(game, &GameModel::turnChanged, this, &GameView::transition);
  }

  void playAgain() {
    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != 0) {
      qDebug() << "Deleting" << child;
      child->widget()->deleteLater();  // delete the widget
      delete child;
    }

    game = new GameModel();

    // Buttons for player choice (friend = button1, robot = button 2)
    buttonFriend = new QPushButton(this);
    buttonComputer = new QPushButton(this);
    QPixmap buttonImageFriend("resources/players/friend.jpg");
    QPixmap buttonImageComputer("resources/players/computer.jpg");
    buttonFriend->setIcon(buttonImageFriend);
    buttonFriend->setIconSize(buttonImageFriend.size());
    buttonComputer->setIcon(buttonImageComputer);
    buttonComputer->setIconSize(buttonImageComputer.size());
    qDebug() << "Play Again :";

    layout->addWidget(buttonFriend, 1, 0);
    layout->addWidget(buttonComputer, 1, 1);

    // connexion of buttons
    connect(buttonFriend, &QPushButton::clicked, this,
            [this]() { handleButton1Clicked(); });

    connect(buttonComputer, &QPushButton::clicked, this,
            [this]() { handleButton2Clicked(); });
  }

  void transition() {
    if (!game->againstRobot()) {
      qDebug() << "Tour : " << game->turn();

      QLayoutItem* child;
      while ((child = layout->takeAt(0)) != 0) {
        qDebug() << "Deleting" << child;
        child->widget()->deleteLater();  // delete the widget
        delete child;
      }
      buttonTransition = new QPushButton(this);

      if (game->turn() % 2 == 0) {
        QPixmap buttonImageTransition("resources/players/player1Wins.png");
        buttonTransition->setIcon(buttonImageTransition);
        buttonTransition->setIconSize(buttonImageTransition.size());
      } else {
        QPixmap buttonImageTransition("resources/players/player1Wins.png");
        buttonTransition->setIcon(buttonImageTransition);
        buttonTransition->setIconSize(buttonImageTransition.size());
      }

      layout->addWidget(buttonTransition, 0, 0);

      // connexion of buttons
      connect(buttonTransition, &QPushButton::clicked, this,
              [this]() { syncPlayer(); });
    }
  }

  void setFinalScreen(size_t playerId) {
    qDebug() << "gagnant :" << playerId;

    // Création d'une nouvelle fenêtre
    QMainWindow* newWindow = new QMainWindow();

    buttonPlayAgain = new QPushButton(this);

    if (playerId == 0) {
      QPixmap buttonImageFriend("resources/players/player1Wins.png");
      buttonPlayAgain->setIcon(buttonImageFriend);
      buttonPlayAgain->setIconSize(buttonImageFriend.size());
    } else if (playerId == 1) {
      if (game->againstRobot()) {
        QPixmap buttonImageFriend("resources/players/player2Wins.png");
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

    qDebug() << "final screen";
  }

  bool reorganizeEndGame() {
    qDebug() << "tour" << game->turn();
    qDebug() << "Change view of player";
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

  void syncPlayer() {
    qDebug() << "INTO SYNC playerid:" << game->getPlayer()->id();
    if (this->game->isEnd()) {
      qDebug() << "INTO ENDED";
      qDebug() << "ended game";
      qDebug() << "tour" << game->turn();

      reorganizeEndGame();
      setFinalScreen(this->game->getWinnerId());
    } else {
      qDebug() << "INTO ELSE";
      // If Robot -> make the robot play

      qDebug() << "Change view of player";
      QLayoutItem* child;
      while ((child = layout->takeAt(0)) != 0) {
        qDebug() << "Deleting" << child;
        child->widget()->deleteLater();  // delete the widget
        delete child;
      }
      qDebug() << "Create child";
      // this->setStyleSheet("border: 1px solid red");

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

      qDebug() << "Create stones";
      if (dynamic_cast<PlayerRobotModel*>(game->getPlayer()) != nullptr) {
        PlayerRobotModel* robotPlayer =
            dynamic_cast<PlayerRobotModel*>(game->getPlayer());

        robotPlayer->playTurn(game->getStones());
        if (!game->getDeck()->isEmpty()) {
          robotPlayer->pickCard(game->getDeck()->draw());
        }

        this->game->nextTurn();

      } else {
        for (StoneModel* stoneModel : game->getStones()) {
          StoneView* stone = new StoneView(stoneModel, game->getPlayer(),
                                           game->getEnemy(), widgetStones);

          layoutStones->addWidget(stone);

          if (!this->game->isEnd()) {
            connect(stone, &StoneView::action, this,
                    [this, stoneModel](StoneView::StoneActionType actionType) {
                      qDebug() << stoneModel;
                      qDebug() << actionType;
                      if ((actionType == StoneView::Formation1 ||
                           actionType == StoneView::Formation2) &&
                          cardViewSelected != nullptr) {
                        qDebug() << "playing";
                        try {
                          qDebug() << "still game";
                          if (!stoneModel->isFull(game->getPlayer())) {
                            this->game->getPlayer()->removeCard(
                                cardViewSelected->getCard());
                            stoneModel->addCard(game->getPlayer(),
                                                cardViewSelected->getCard());
                            cardViewSelected = nullptr;
                            if (!this->game->getDeck()->isEmpty()) {
                              this->game->getPlayer()->pickCard(
                                  this->game->getDeck()->draw());
                            }
                            this->game->nextTurn();
                          }
                        } catch (...) {
                          qDebug() << "not in deck";
                        }
                      }
                    });
          }
        }
      }
    }

    // game->getStones()[0]->addPlayer1Card(game->getDeck()->draw());
    syncHand(game->getPlayer()->getCards());
    syncEnemyHand(game->getEnemy()->getCards());
    // connect(game->getPlayer(), &PlayerModel::changedCards, this,
    // &GameView::syncHand); connect(game->getEnemy(),
    // &PlayerModel::changedCards, this, &GameView::syncEnemyHand);

    // layout->addWidget(widgetHand, 2, 0);
    qDebug() << "Created game view";
  }

  void resize() {
    qDebug() << "FONT";
    // TODO(Dashstrom): crash here
    /*
    resizeFactor = (width() / 700.0) * 100;
    qDebug() << resizeFactor;
    deckCountLabel->setFont(
        QFont("Impact", 10 * resizeFactor / 100, QFont::Normal));
    playerTurnLabel->setFont(
        QFont("Impact", 15 * resizeFactor / 100, QFont::Bold));
    */
    qDebug() << "END";
  }

 protected:
  void paintEvent(QPaintEvent* e) override {
    QPainter painter(this);
    painter.drawPixmap(0, 0,
                       QPixmap("resources/woods/wood.28.png").scaled(size()));
    QWidget::paintEvent(e);
  }

  void resizeEvent(QResizeEvent* event) override {
    qDebug() << "resizeEvent game view";
    // Call the base class implementation
    QWidget::resizeEvent(event);
    resize();
  }

 private:
  void syncHand(const QList<CardModel*> cards) {
    qDebug() << "Syncing hand";
    cardViewSelected = nullptr;
    qDeleteAll(
        widgetHand->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
    qDebug() << "Deleted hand";
    for (CardModel* cardModel : cards) {
      CardView* cardView = new CardView(cardModel, widgetHand);
      layoutHand->addWidget(cardView);
      connect(cardView, &CardView::clicked, [cards, cardView, this]() {
        if (cardViewSelected != nullptr) {
          cardViewSelected->setSelected(false);
        }
        cardView->setSelected(true);
        cardViewSelected = cardView;
      });
    }

    QWidget* playerTurn = new QWidget();
    QVBoxLayout* layoutPlayerTurn = new QVBoxLayout(playerTurn);

    playerTurnLabel = new QLabel(
        QString("Tour du joueur %1").arg(game->getPlayer()->id() + 1));

    QPalette playerTurnPalette = playerTurnLabel->palette();
    playerTurnPalette.setColor(QPalette::WindowText, Qt::white);
    playerTurnLabel->setPalette(playerTurnPalette);
    playerTurnLabel->setFont(QFont("Impact", 15, QFont::Bold));
    playerTurnLabel->setWordWrap(true);

    layoutPlayerTurn->addWidget(playerTurnLabel);

    deckCountLabel = new QLabel(QString("Cartes restantes dans la pioche : %1")
                                    .arg(game->getDeck()->countCards()));

    QPalette deckCountPalette = deckCountLabel->palette();
    deckCountPalette.setColor(QPalette::WindowText, Qt::white);
    deckCountLabel->setPalette(deckCountPalette);
    deckCountLabel->setFont(QFont("Impact", 10, QFont::Normal));
    deckCountLabel->setWordWrap(true);

    layoutPlayerTurn->addWidget(deckCountLabel);

    layoutHand->addWidget(playerTurn);
    qDebug() << "Synced hand";
  }

  void syncEnemyHand(const QList<CardModel*> cards) {
    qDeleteAll(widgetEnemyHand->findChildren<QWidget*>(
        "", Qt::FindDirectChildrenOnly));
    for (int i = 0; i < cards.count(); i++) {
      layoutEnemyHand->addWidget(
          new ButtonView("resources/cards/hidden.png", widgetEnemyHand));
    }
  }
};
