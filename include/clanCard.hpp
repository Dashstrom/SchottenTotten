#pragma once

#include <QColor>
#include <QLabel>

enum class ClanCardColor { Green, Blue, Red, Yellow, Purple, Brown };

class ClanCard : public QLabel {
  Q_OBJECT

public:
  ClanCard(int s = 0, ClanCardColor c = ClanCardColor::Green);

  int getStrength() const { return strength; };
  ClanCardColor getColor() const { return color; };
  QString getBackgroundColor() const { return backgroundColor; };

  // TODO : add setters with validation (>= 1 && <= 6 ...)

signals:
  void clicked(ClanCard *clanCard);

protected:
  void mousePressEvent(QMouseEvent *event) override {
    // Emit the custom clicked signal
    emit clicked(this);

    // Call the base class implementation
    QLabel::mousePressEvent(event);
  }

private:
  QString backgroundColor;
  int strength;
  ClanCardColor color;
};
