/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

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
#include "game_robot_model.hpp"

GameView::GameView(QWidget* parent) : QWidget(parent) {
  qDebug() << "Creating game view";
  m_layout = new QGridLayout(this);
  m_game = nullptr;
  playAgain();
}

void GameView::handleButton1Clicked() {
  m_game = new GameModel();
  m_againstRobot = false;
  m_buttonFriend->hide();
  m_buttonComputer->hide();
  transition();
}
void GameView::handleButton2Clicked() {
  m_game = new GameRobotModel();
  m_againstRobot = true;
  m_buttonFriend->hide();
  m_buttonComputer->hide();
  transition();
}

void GameView::syncPlayer() {
  clearBoard();

  m_widgetStones = new QWidget(this);
  m_layoutStones = new QHBoxLayout(m_widgetStones);
  m_layoutStones->setContentsMargins(0, 0, 0, 0);
  m_layoutStones->setSpacing(10);

  m_widgetHand = new QWidget(this);
  m_layoutHand = new QHBoxLayout(m_widgetHand);

  m_widgetEnemyHand = new QWidget(this);
  m_layoutEnemyHand = new QHBoxLayout(m_widgetEnemyHand);

  m_layout->addWidget(m_widgetEnemyHand, 0, 0);
  m_layout->addWidget(m_widgetStones, 1, 0);
  m_layout->addWidget(m_widgetHand, 2, 0);

  // define the relative proportions of the rows
  m_layout->setRowStretch(0, 1);
  m_layout->setRowStretch(1, 3);
  m_layout->setRowStretch(2, 1);
  m_layout->setColumnStretch(0, 1);
  m_layout->setColumnStretch(1, 0);

  qDebug() << "Create stones";
  for (size_t i = 0; i < STONE_COUNT; i++) {
    StoneModel& stoneModel = m_game->getStones()[i];
    StoneView* m_stone = new StoneView(stoneModel, m_game->getPlayer(),
                                       m_game->getEnemy(), i, m_widgetStones);

    m_layoutStones->addWidget(m_stone);

    if (!this->m_game->isEnd()) {
      connect(m_stone, &StoneView::action, this,
              [this, &stoneModel](StoneView::StoneActionType actionType) {
                handleStoneAction(stoneModel, actionType);
              });
    }
  }

  syncHand(m_game->getPlayer().getCards());
  syncEnemyHand(m_game->getEnemy().getCards());
  if (this->m_game->isEnd()) {
    setFinalScreen(this->m_game->getWinnerId());
  }
  qDebug() << "Created game view";
}

void GameView::handleStoneAction(StoneModel& m_stone,
                                 StoneView::StoneActionType action) {
  if ((action == StoneView::Formation1 || action == StoneView::Formation2 ||
       action == StoneView::Stone) &&
      m_cardViewSelected != nullptr) {
    qDebug() << "playing";
    try {
      if (!m_stone.isFull(m_game->getPlayer())) {
        this->m_game->getPlayer().removeCard(m_cardViewSelected->getCard());
        m_stone.addCard(m_game->getPlayer(), m_cardViewSelected->getCard());
        m_cardViewSelected = nullptr;
        if (!this->m_game->getDeck().isEmpty()) {
          this->m_game->getPlayer().pickCard(this->m_game->getDeck().draw());
        }
        this->m_game->nextTurn();
        transition();
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
  m_cardViewSelected = nullptr;
  qDeleteAll(
      m_widgetHand->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));
  qDebug() << "Deleted hand";
  for (CardModel* cardModel : cards) {
    CardView* cardView = new CardView(cardModel, m_widgetHand);
    m_layoutHand->addWidget(cardView);
    connect(cardView, &CardView::clicked, [cards, cardView, this]() {
      if (m_cardViewSelected != nullptr) {
        m_cardViewSelected->setSelected(false);
      }
      cardView->setSelected(true);
      m_cardViewSelected = cardView;
    });
  }

  QWidget* playerTurn = new QWidget();
  QVBoxLayout* layoutPlayerTurn = new QVBoxLayout(playerTurn);

  m_playerTurnLabel = new QLabel(
      QString("Tour du joueur %1").arg(m_game->getPlayer().id() + 1));

  QPalette playerTurnPalette = m_playerTurnLabel->palette();
  playerTurnPalette.setColor(QPalette::WindowText, Qt::white);
  m_playerTurnLabel->setPalette(playerTurnPalette);
  m_playerTurnLabel->setFont(QFont("Impact", 15, QFont::Bold));
  m_playerTurnLabel->setWordWrap(true);

  layoutPlayerTurn->addWidget(m_playerTurnLabel);

  m_deckCountLabel = new QLabel(QString("Cartes restantes dans la pioche : %1")
                                    .arg(m_game->getDeck().countCards()));

  QPalette deckCountPalette = m_deckCountLabel->palette();
  deckCountPalette.setColor(QPalette::WindowText, Qt::white);
  m_deckCountLabel->setPalette(deckCountPalette);
  m_deckCountLabel->setFont(QFont("Impact", 10, QFont::Normal));
  m_deckCountLabel->setWordWrap(true);

  layoutPlayerTurn->addWidget(m_deckCountLabel);

  m_layoutHand->addWidget(playerTurn);
  qDebug() << "Synced hand";
}

void GameView::syncEnemyHand(const QList<CardModel*> cards) {
  qDeleteAll(m_widgetEnemyHand->findChildren<QWidget*>(
      "", Qt::FindDirectChildrenOnly));
  for (int i = 0; i < cards.count(); i++) {
    m_layoutEnemyHand->addWidget(
        new ButtonView("resources/hidden.jpg", m_widgetEnemyHand));
  }
}

void GameView::playAgain() {
  clearBoard();
  if (m_game != nullptr) {
    delete m_game;
  }

  // Buttons for player choice (friend = button1, robot = button 2)
  m_buttonFriend = new ButtonView("resources/players/friend.jpg", this);
  m_buttonComputer = new ButtonView("resources/players/computer.jpg", this);
  qDebug() << "Play Again :";

  m_layout->addWidget(m_buttonFriend, 0, 0);
  m_layout->addWidget(m_buttonComputer, 0, 1);
  m_layout->setColumnStretch(0, 1);
  m_layout->setColumnStretch(1, 1);
  m_layout->setRowStretch(0, 1);
  m_layout->setRowStretch(1, 0);
  m_layout->setRowStretch(2, 0);

  // connexion of buttons
  connect(m_buttonFriend, &ButtonView::clicked, this,
          [this]() { handleButton1Clicked(); });

  connect(m_buttonComputer, &ButtonView::clicked, this,
          [this]() { handleButton2Clicked(); });
}

// Display who's turn to play
void GameView::transition() {
  clearBoard();
  if (m_againstRobot) {
    syncPlayer();
    return;
  }
  m_layout->setColumnStretch(0, 1);
  m_layout->setColumnStretch(1, 0);
  m_layout->setRowStretch(0, 1);
  m_layout->setRowStretch(1, 0);
  m_layout->setRowStretch(2, 0);

  if (m_game->turn() % 2 == 0) {
    m_buttonTransition =
        new ButtonView("resources/players/player1Turn.png", this, false);
  } else {
    m_buttonTransition =
        new ButtonView("resources/players/player2Turn.png", this, false);
  }

  m_layout->addWidget(m_buttonTransition, 0, 0);

  connect(m_buttonTransition, &ButtonView::clicked, this,
          [this]() { syncPlayer(); });
}

void GameView::clearBoard() {
  qDebug() << "Change view of player";
  QLayoutItem* child;
  while ((child = m_layout->takeAt(0)) != 0) {
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
  QVBoxLayout* m_layout = new QVBoxLayout(dialog);
  m_layout->setContentsMargins(0, 0, 0, 0);

  QString path("resources/players/noOneWon.png");
  if (playerId == 0) {
    path = "resources/players/player1Wins.png";
  } else if (playerId == 1) {
    if (m_againstRobot) {
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
  m_layout->addWidget(buttonPlayAgain);
  dialog->show();
}
