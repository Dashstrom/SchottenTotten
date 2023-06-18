/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#include "game_view.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "button_view.hpp"
#include "game_model.hpp"
#include "player_robot_model.hpp"

GameView::GameView(QWidget* parent) : QWidget(parent) {
  qDebug() << "Creating game view";
  layout = new QGridLayout(this);
  game = nullptr;
  playAgain();
}

void GameView::handleButton1Clicked() {
  buttonFriend->hide();
  buttonComputer->hide();
  transition();
  connect(game, &GameModel::turnChanged, this, &GameView::transition);
}
void GameView::handleButton2Clicked() {
  buttonFriend->hide();
  buttonComputer->hide();
  PlayerRobotModel* robot = new PlayerRobotModel(1);

  game->setRobot(robot);
  transition();
  connect(game, &GameModel::turnChanged, this, &GameView::transition);
}

void GameView::syncPlayer() {
  clearBoard();
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
  layout->setColumnStretch(0, 1);
  layout->setColumnStretch(1, 0);

  qDebug() << "Create stones";

  // If Robot -> make the robot play
  if (dynamic_cast<PlayerRobotModel*>(game->getPlayer()) != nullptr) {
    PlayerRobotModel* robotPlayer =
        dynamic_cast<PlayerRobotModel*>(game->getPlayer());
    robotPlayer->playTurn(game->getStones());
    if (!game->getDeck()->isEmpty()) {
      robotPlayer->pickCard(game->getDeck()->draw());
    }
    this->game->nextTurn();

    if (this->game->isEnd()) {
      int i = 0;
      for (StoneModel* stoneModel : game->getStones()) {
        StoneView* stone = new StoneView(stoneModel, game->getPlayer(),
                                         game->getEnemy(), i++, widgetStones);

        layoutStones->addWidget(stone);
      }
    }
  } else {
    int i = 0;
    for (StoneModel* stoneModel : game->getStones()) {
      StoneView* stone = new StoneView(stoneModel, game->getPlayer(),
                                       game->getEnemy(), i++, widgetStones);

      layoutStones->addWidget(stone);

      if (!this->game->isEnd()) {
        connect(stone, &StoneView::action, this,
                [this, stoneModel](StoneView::StoneActionType actionType) {
                  handleStoneAction(stoneModel, actionType);
                });
      }
    }
  }

  syncHand(game->getPlayer()->getCards());
  syncEnemyHand(game->getEnemy()->getCards());
  if (this->game->isEnd()) {
    setFinalScreen(this->game->getWinnerId());
  }
  qDebug() << "Created game view";
}

void GameView::handleStoneAction(StoneModel* stone,
                                 StoneView::StoneActionType action) {
  qDebug() << stone;
  qDebug() << action;
  if ((action == StoneView::Formation1 || action == StoneView::Formation2 ||
       action == StoneView::Stone) &&
      cardViewSelected != nullptr) {
    qDebug() << "playing";
    try {
      if (!stone->isFull(game->getPlayer())) {
        this->game->getPlayer()->removeCard(cardViewSelected->getCard());
        stone->addCard(game->getPlayer(), cardViewSelected->getCard());
        cardViewSelected = nullptr;
        if (!this->game->getDeck()->isEmpty()) {
          this->game->getPlayer()->pickCard(this->game->getDeck()->draw());
        }
        this->game->nextTurn();
      }
    } catch (...) {
      qDebug() << "not in deck";
    }
  }
}

void GameView::paintEvent(QPaintEvent* e) {
  QPainter painter(this);
  painter.drawPixmap(0, 0, QPixmap("resources/background.jpg").scaled(size()));
  QWidget::paintEvent(e);
}

void GameView::syncHand(const QList<CardModel*> cards) {
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

  playerTurnLabel =
      new QLabel(QString("Tour du joueur %1").arg(game->getPlayer()->id() + 1));

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

void GameView::syncEnemyHand(const QList<CardModel*> cards) {
  qDeleteAll(
      widgetEnemyHand->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
  for (int i = 0; i < cards.count(); i++) {
    layoutEnemyHand->addWidget(
        new ButtonView("resources/hidden.jpg", widgetEnemyHand));
  }
}

void GameView::playAgain() {
  clearBoard();
  if (game != nullptr) {
    delete game;
  }
  game = new GameModel();

  // Buttons for player choice (friend = button1, robot = button 2)
  buttonFriend = new ButtonView("resources/players/friend.jpg", this);
  buttonComputer = new ButtonView("resources/players/computer.jpg", this);
  qDebug() << "Play Again :";

  layout->addWidget(buttonFriend, 0, 0);
  layout->addWidget(buttonComputer, 0, 1);
  layout->setColumnStretch(0, 1);
  layout->setColumnStretch(1, 1);
  layout->setRowStretch(0, 1);
  layout->setRowStretch(1, 0);
  layout->setRowStretch(2, 0);

  // connexion of buttons
  connect(buttonFriend, &ButtonView::clicked, this,
          [this]() { handleButton1Clicked(); });

  connect(buttonComputer, &ButtonView::clicked, this,
          [this]() { handleButton2Clicked(); });
}

// Display who's turn to play
void GameView::transition() {
  if (!game->againstRobot()) {
    clearBoard();
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 0);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 0);
    layout->setRowStretch(2, 0);

    if (game->turn() % 2 == 0) {
      buttonTransition =
          new ButtonView("resources/players/player1Turn.png", this, false);
    } else {
      buttonTransition =
          new ButtonView("resources/players/player2Turn.png", this, false);
    }

    layout->addWidget(buttonTransition, 0, 0);

    connect(buttonTransition, &ButtonView::clicked, this,
            [this]() { syncPlayer(); });
  } else {
    syncPlayer();
  }
}

void GameView::clearBoard() {
  qDebug() << "Change view of player";
  QLayoutItem* child;
  while ((child = layout->takeAt(0)) != 0) {
    qDebug() << "Deleting" << child;
    child->widget()->deleteLater();  // delete the widget
    delete child;
  }
  qDebug() << "Create child";
}

void GameView::setFinalScreen(size_t playerId) {
  // Création d'une nouvelle fenêtre
  QDialog* dialog = new QDialog(this);
  dialog->setModal(true);
  dialog->show();
  dialog->setWindowTitle("Schotten Totten");
  dialog->setModal(true);
  QIcon icon("resources/favicon.ico");
  dialog->setMaximumHeight(450);
  dialog->setMinimumHeight(450);
  dialog->setMaximumWidth(800);
  dialog->setMinimumWidth(800);
  dialog->setWindowIcon(icon);
  QVBoxLayout* layout = new QVBoxLayout(dialog);
  layout->setContentsMargins(0, 0, 0, 0);

  QString path("resources/players/noOneWon.png");
  if (playerId == 0) {
    path = "resources/players/player1Wins.png";
  } else if (playerId == 1) {
    if (game->againstRobot()) {
      path = "resources/players/robotWins.png";
    } else {
      path = "resources/players/player2Wins.png";
    }
  }
  ButtonView* buttonPlayAgain = new ButtonView(path, dialog, true);

  connect(buttonPlayAgain, &ButtonView::clicked, this,
          [this, dialog]() { dialog->accept(); });
  connect(dialog, &QDialog::finished, this,
          [this, dialog](int result) { playAgain(); });
  layout->addWidget(buttonPlayAgain);
  dialog->show();
}
