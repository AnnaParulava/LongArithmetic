/*�������� ����� IntHuge (������� �����, �������������� �������� ��������)
� ���������� +, +=, -, -=, =, ==, !=, >, <, >=, <=, *, *=, *(int) (��������� �� ���������). */

#pragma once
#ifndef INTHUGE_H_INCLUDED
#define INTHUGE_H_INCLUDED

#include <algorithm> //������� ����������� ���������
#include <string> //����� ������������ ������
#include <exception> //����������
#include <vector> //�������� vector-��
#include <sstream> //��������� ������ ��� �������������� �����
#include <iomanip>

class IntHuge{
public:
  IntHuge(); //����������� �� ���������
  IntHuge(std::string number); //����������� �� ������
  IntHuge(long long number); //����������� �� �������� ������
  IntHuge(const IntHuge& rhs); //����������� �����������

  //��������� ������������
  IntHuge& operator=(const IntHuge& rhs);
  IntHuge& operator+=(const IntHuge& rhs);
  IntHuge& operator-=(const IntHuge& rhs);
  IntHuge& operator*=(const IntHuge& rhs);

  //��������� ��������� � ���������
  bool operator>(const IntHuge& rhs) const;
  bool operator<(const IntHuge& rhs) const;
  bool operator==(const IntHuge& rhs) const;
  bool operator>=(const IntHuge& rhs) const;
  bool operator<=(const IntHuge& rhs) const;
  bool operator!=(const IntHuge& rhs) const;

  //��������� ����-�����
  friend std::istream& operator>>(std::istream& inStream, IntHuge& intHuge);
  friend std::ostream& operator<<(std::ostream& outStream, IntHuge& intHuge);

  //�������������� ��������
  const IntHuge operator+(const IntHuge& rhs) const;
  const IntHuge operator-(const IntHuge& rhs) const;
  const IntHuge operator*(const IntHuge& rhs) const;

  std::string to_string() const; //���������� � ����������� ����

  IntHuge abs() const; //���������� �������� ������ �����

private:
  void removeLeadingZeros(); //������� ������� ����
  IntHuge mul(unsigned int digit) const;

  int digit(int index) const;

  std::vector<unsigned int> digits; //������ ����
  bool sign; //������ ��� �����
};

#endif // INTHUGE_H_INCLUDED
