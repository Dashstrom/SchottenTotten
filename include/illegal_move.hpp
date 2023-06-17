/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once
#include <QString>

class IllegalMove : public std::exception {
 private:
  QString message;

 public:
  MonException(const QString& msg) : message(msg) {}

  virtual const char* what() const throw() { return message.c_str(); }
};
