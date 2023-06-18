/*
   Copyright 2023
   Dashstrom, Marin Bouanchaud, ericluo-lab, Soudarsane TILLAI, Baptiste Buvron
 */
#ifndef INCLUDE_ILLEGAL_MOVE_EXCEPTION_HPP_
#define INCLUDE_ILLEGAL_MOVE_EXCEPTION_HPP_

#include <QString>
#include <exception>

class IllegalMoveException : public std::exception {
 private:
  QString message;

 public:
  explicit IllegalMoveException(const QString& msg = "unkown") : message(msg) {}

  virtual const char* what() const throw() {
    return message.toStdString().c_str();
  }
};

#endif  // INCLUDE_ILLEGAL_MOVE_EXCEPTION_HPP_
