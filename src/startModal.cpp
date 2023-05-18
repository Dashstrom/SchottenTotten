#include "startModal.hpp"

StartModal::StartModal(Game *game, QWidget *parent)
    : QDialog(parent), game(game) {
  setWindowTitle("Start Schotten Totten");
  setModal(true);
  setMinimumWidth(300);

  QVBoxLayout *layout = new QVBoxLayout(this);
  QPushButton *startButton = new QPushButton("Start Game : 2 players", this);
  QPushButton *start1PlayerButton =
      new QPushButton("Start Game : 1 player with IA (soon...)", this);

  layout->addWidget(startButton);
  layout->addWidget(start1PlayerButton); // TODO: inactive

  QObject::connect(startButton, SIGNAL(clicked()), this,
                   SLOT(onStartGameButtonClicked()));

  show();
}

void StartModal::onStartGameButtonClicked() {
  this->accept(); // Close the start window
  game->launch();
}