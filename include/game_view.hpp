/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QPushButton>
#include <QSizePolicy>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "card_model.hpp"
#include "card_view.hpp"
#include "game_model.hpp"
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

  int resizeFactor = 100;

 public:
  explicit GameView(GameModel* model, QWidget* parent = nullptr)
      : QWidget(parent) {
    qDebug() << "Creating game view";
    game = model;

    layout = new QGridLayout(this);
    syncPlayer();
    connect(game, &GameModel::turnChanged, this, &GameView::syncPlayer);
  }

  void syncPlayer() {
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
    qDebug() << "Created game view";
  }

  void resize() {
    resizeFactor = (width() / 700.0) * 100;
    deckCountLabel->setFont(
        QFont("Impact", 10 * resizeFactor / 100, QFont::Normal));
    playerTurnLabel->setFont(
        QFont("Impact", 15 * resizeFactor / 100, QFont::Bold));
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
    for (CardModel* cardModel : cards) {
      layoutEnemyHand->addWidget(
          new ButtonView("resources/cards/hidden.png", widgetEnemyHand));
    }
  }
};