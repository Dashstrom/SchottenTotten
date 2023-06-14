/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPaintEvent>
#include <QPainter>
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

  CardLayout* layoutHand;
  QWidget* widgetHand;

  CardLayout* layoutEnemyHand;
  QWidget* widgetEnemyHand;

  CardView* cardViewSelected = nullptr;

  GameModel* game;

  // TEST
  QPushButton* button1;
  QPushButton* button2;

 public:
  explicit GameView(GameModel* model, QWidget* parent = nullptr)
      : QWidget(parent) {
    qDebug() << "Creating game view";
    game = model;
    layout = new QGridLayout(this);

    // Button for player choice (friend, robot)
    button1 = new QPushButton(this);
    button2 = new QPushButton(this);
    QPixmap buttonImage1("resources/players/easy.png");
    QPixmap buttonImage2("resources/players/hard.png");
    button1->setIcon(buttonImage1);
    button1->setIconSize(buttonImage1.size());
    button2->setIcon(buttonImage2);
    button2->setIconSize(buttonImage2.size());

    layout->addWidget(button1, 0, 0);
    layout->addWidget(button2, 0, 1);

    // connexion of buttons
    connect(button1, &QPushButton::clicked, this,
            [this]() { handleButton1Clicked(); });

    connect(button2, &QPushButton::clicked, this,
            [this]() { handleButton2Clicked(); });
  }

  void handleButton1Clicked() {
    button1->hide();
    button2->hide();
    game->setRobot(new PlayerRobotModel(1, 1));
    syncPlayer();
    connect(game, &GameModel::turnChanged, this, &GameView::syncPlayer);
  }
  void handleButton2Clicked() {
    button1->hide();
    button2->hide();
    game->setRobot(new PlayerRobotModel(1, 2));
    syncPlayer();
    connect(game, &GameModel::turnChanged, this, &GameView::syncPlayer);
  }

  void syncPlayer() {
    if (dynamic_cast<PlayerRobotModel*>(game->getPlayer()) != nullptr) {
      PlayerRobotModel* robotPlayer =
          dynamic_cast<PlayerRobotModel*>(game->getPlayer());
      robotPlayer->playTurn(game);
    }

    qDebug() << "Change view of player";
    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != 0) {
      qDebug() << "Deleting" << child;
      child->widget()->deleteLater();  // delete the widget
      delete child;
    }
    qDebug() << "Create child";
    this->setStyleSheet("border: 1px solid red");

    widgetStones = new QWidget(this);
    layoutStones = new QHBoxLayout(widgetStones);
    layoutStones->setContentsMargins(0, 0, 0, 0);
    layoutStones->setSpacing(0);

    widgetHand = new QWidget(this);
    layoutHand = new CardLayout(90, 0, widgetHand);

    widgetEnemyHand = new QWidget(this);
    layoutEnemyHand = new CardLayout(90, 0, widgetEnemyHand);

    layout->addWidget(widgetEnemyHand, 0, 0);
    layout->addWidget(widgetStones, 1, 0);
    layout->addWidget(widgetHand, 2, 0);

    // define the relative proportions of the rows
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 3);
    layout->setRowStretch(2, 1);

    qDebug() << "Create stones";
    for (StoneModel* stoneModel : game->getStones()) {
      StoneView* stone = new StoneView(stoneModel, game->getPlayer(),
                                       game->getEnemy(), widgetStones);
      layoutStones->addWidget(stone);
      connect(stone, &StoneView::action, this,
              [this, stoneModel](StoneView::StoneActionType actionType) {
                qDebug() << stoneModel;
                qDebug() << actionType;
                if ((actionType == StoneView::Formation1 ||
                     actionType == StoneView::Formation2) &&
                    cardViewSelected != nullptr) {
                  qDebug() << "playing";
                  try {
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

    // game->getStones()[0]->addPlayer1Card(game->getDeck()->draw());
    syncHand(game->getPlayer()->getCards());
    syncEnemyHand(game->getEnemy()->getCards());
    // connect(game->getPlayer(), &PlayerModel::changedCards, this,
    // &GameView::syncHand); connect(game->getEnemy(),
    // &PlayerModel::changedCards, this, &GameView::syncEnemyHand);

    // layout->addWidget(widgetHand, 2, 0);

    qDebug() << "Created game view";
  }

 protected:
  void paintEvent(QPaintEvent* e) {
    QPainter painter(this);
    painter.drawPixmap(0, 0,
                       QPixmap("resources/woods/wood.28.png").scaled(size()));
    QWidget::paintEvent(e);
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
