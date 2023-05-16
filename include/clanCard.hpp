#pragma once

enum class ClanCardColor { Green, Blue, Red, Yellow, Purple, Brown };

class ClanCard {
public:
  ClanCard() : strength(0), color(ClanCardColor::Green){};
  ClanCard(int s, ClanCardColor c) : strength(s), color(c){};
  int getStrength() const { return strength; };
  ClanCardColor getColor() const { return color; };

  // TODO : add setters with validation (>= 1 && <= 6 ...)

private:
  int strength;
  ClanCardColor color;
};
