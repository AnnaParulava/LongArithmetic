/*—оздайте класс IntHuge (длинные целые, представленные массивом разр€дов)
с операци€ми +, +=, -, -=, =, ==, !=, >, <, >=, <=, *, *=, *(int) (умножение на константу). */

#pragma once
#ifndef INTHUGE_H_INCLUDED
#define INTHUGE_H_INCLUDED

#include <algorithm> //функции выполн€ющие алгоритмы
#include <string> //чтобы использовать строки
#include <exception> //исключени€
#include <vector> //описание vector-ов
#include <sstream> //строковые потоки дл€ преобразовани€ чисел
#include <iomanip>

class IntHuge{
public:
  IntHuge(); //конструктор по умолчанию
  IntHuge(std::string number); //конструктор по строке
  IntHuge(long long number); //конструктор по длинному целому
  IntHuge(const IntHuge& rhs); //конструктор копировани€

  //операторы присваивани€
  IntHuge& operator=(const IntHuge& rhs);
  IntHuge& operator+=(const IntHuge& rhs);
  IntHuge& operator-=(const IntHuge& rhs);
  IntHuge& operator*=(const IntHuge& rhs);

  //операторы сравнени€ и равенства
  bool operator>(const IntHuge& rhs) const;
  bool operator<(const IntHuge& rhs) const;
  bool operator==(const IntHuge& rhs) const;
  bool operator>=(const IntHuge& rhs) const;
  bool operator<=(const IntHuge& rhs) const;
  bool operator!=(const IntHuge& rhs) const;

  //потоковый ввод-вывод
  friend std::istream& operator>>(std::istream& inStream, IntHuge& intHuge);
  friend std::ostream& operator<<(std::ostream& outStream, IntHuge& intHuge);

  //арифметические операции
  const IntHuge operator+(const IntHuge& rhs) const;
  const IntHuge operator-(const IntHuge& rhs) const;
  const IntHuge operator*(const IntHuge& rhs) const;

  std::string to_string() const; //приведение к стороковому типу

  IntHuge abs() const; //абсолютное значение целого числа

private:
  void removeLeadingZeros(); //удалить ведущие нули
  IntHuge mul(unsigned int digit) const;

  int digit(int index) const;

  std::vector<unsigned int> digits; //массив цифр
  bool sign; //флажок дл€ знака
};

#endif // INTHUGE_H_INCLUDED
