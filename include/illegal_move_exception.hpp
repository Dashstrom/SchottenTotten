/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#pragma once
#include <QString>

class IllegalMoveException : public std::exception {
 private:
  QString message;

 public:
  IllegalMoveException(const QString& msg) : message(msg) {}

  virtual const char* what() const throw() { return message.toStdString().c_str(); }
};
