#include "IntHuge.h"


//����������� �� ���������
IntHuge::IntHuge(){
  digits.push_back(0); //���������������� ������ ���� �����
  sign = true; //����������� ������������� ����
}


//����������� �� ������
IntHuge::IntHuge(std::string number){
if (number[0] == '-') //����������� ������ ������ �� ������� �����
 this->sign = false;
else
 this->sign = true;

 int pos = isdigit(number[0]) ? 0 : 1;
 for(unsigned int i = pos; i < number.length(); i++){//��������� ����� �������� � ������
    digits.push_back(number[i] - '0');    //��� ���� ����������� ������ � �����
  }

  removeLeadingZeros(); //������� ������� ����
}

//����������� �� �������� ������
IntHuge::IntHuge(long long number)
  : IntHuge(std::to_string(number)) { //������������� �������� � ���� string � �������� ���������� ���������������� ������������
}

//����������� �����������
IntHuge::IntHuge(const IntHuge& rhs){
  sign = rhs.sign;
  digits = rhs.digits;
}

//���������� � ���������� ����
std::string IntHuge::to_string() const{
  std::string str;
  if(!sign)
    str+="-";
  for(unsigned int i = 0; i < digits.size(); i++)
    str += std::to_string(digits.at(i));
  return str;
}

//�������� ������� �����
void IntHuge::removeLeadingZeros(){
  while(digits.size() > 1 && digits.at(0) == 0)
    digits.erase(digits.begin(), digits.begin() + 1);
}

//����
std::istream& operator>>(std::istream& ist, IntHuge& intHuge){
  std::string number;
  ist >> number;
  intHuge = IntHuge(number);
  return ist;
}

//�����
std::ostream& operator<<(std::ostream& ost, IntHuge& intHuge){
  ost << intHuge.to_string();
  return ost;
}

//�������� ������������
IntHuge& IntHuge::operator=(const IntHuge& rhs){
  if(this == &rhs) //�������� �� ����������������
    return *this;
  sign = rhs.sign;
  digits = rhs.digits;
  return *this;
}

//�������� ��������� >
bool IntHuge::operator>(const IntHuge& rhs) const{

  //�������� �����
  if(sign && !rhs.sign) return true;
  if(!sign && rhs.sign) return false;

  //�������� ���������� ����� � �����
  if(digits.size() > rhs.digits.size())
    return sign;
  if(digits.size() < rhs.digits.size())
    return !sign;

  //��������� ��������, ������� �� �������
  for(size_t i = 0; i < digits.size(); i++) {
    if(digits[i] > rhs.digits[i]) //��������� ���� �� ������� �������������� �������
      return sign;
    if(digits[i] < rhs.digits[i])
      return !sign;
  }

  return false;
}

//�������� ��������� <
bool IntHuge::operator<(const IntHuge& rhs) const{
  return !(*this == rhs) && !(*this > rhs);
}

//�������� ��������� ==
bool IntHuge::operator==(const IntHuge& rhs) const{
  return (sign == rhs.sign && digits == rhs.digits);
}

//�������� ��������� !=
bool IntHuge::operator!=(const IntHuge& rhs) const{
  return !(*this == rhs);
}

//�������� ��������� <=
bool IntHuge::operator<=(const IntHuge& rhs) const{
  return (*this == rhs) || !(*this > rhs);
}

//�������� ��������� >=
bool IntHuge::operator>=(const IntHuge& rhs) const{
  return (*this == rhs) || (*this > rhs);
}


//��������� ������ �����
IntHuge IntHuge::abs() const{
  IntHuge a(*this); //������� ����� ���������
  a.sign = true; //�������� � ���� ���� �����
  return a;
}

//���������� i-��� ������ ����� ��� ���� ���� ������ �������������
int IntHuge::digit(int index) const {
  return index >= 0 ? digits[index] : 0;
}

//������������� �������� �������� (� �������)
const IntHuge IntHuge::operator+(const IntHuge& rhs) const{
  IntHuge sum;
  if(sign == rhs.sign){ //�������� ���������� �� ����
    sum.digits.clear();
    sum.sign = sign;
    unsigned int carry = 0; //���� �������� �� ����������� �������
    int index1 = digits.size() - 1;
    int index2 = rhs.digits.size() - 1;
    while(index1 >=0 || index2 >= 0){ //������������ ������� ����� ������ ������
      auto digitsum = this->digit(index1) + rhs.digit(index2) + carry;

      carry = digitsum / 10;
      digitsum %= 10;

      sum.digits.push_back(digitsum); //����� � ���������� ����������� � �����
      index1--;
      index2--;
    }
    if(carry != 0)
      sum.digits.push_back(carry);
    std::reverse(sum.digits.begin(), sum.digits.end()); //����������� ���������
  } else{ //�������� �� �������� �� ������
    if(this->abs() > rhs.abs()){
      sum = this->abs() - rhs.abs();
      sum.sign = sign;
    } else{
      sum = rhs.abs() - this->abs();
      sum.sign = rhs.sign; //���� ���������� ��������� � ������� �� ������
    }
  }
  return sum;
}

//������������� �������� ��������
const IntHuge IntHuge::operator-(const IntHuge& rhs) const{
  IntHuge difference;
  if(sign == rhs.sign) { //�������� �� ���������� �����
    if(this->abs() > rhs.abs() || this->abs() == rhs.abs()){ //�������� �� �������� ������� �� ������
      difference.digits.clear();
      int index1 = digits.size() - 1;
      int index2 = rhs.digits.size() - 1;
      int borrow = 0;
      difference.sign = sign;
      while(index1 >= 0 || index2 >= 0){
        auto digitdiff = this->digit(index1) - rhs.digit(index2) - borrow;

        if(digitdiff < 0){//���� ������ ���������� ������������� - ����� "������" 10
            borrow = 1;
            digitdiff += 10;
        } else borrow = 0;

        difference.digits.push_back(digitdiff);
        index1--;
        index2--;
      }
      std::reverse(difference.digits.begin(), difference.digits.end());
      difference.removeLeadingZeros();
    } else { //������ �����
      difference = (rhs - (*this));
      difference.sign = !difference.sign;
    }
  } else{ //����� �������, ����������� ��������
    difference = this->abs() + rhs.abs();
    difference.sign = sign;
  }
  return difference;
}

//�������� ��������� �������� ������
IntHuge& IntHuge::operator -=(const IntHuge& rhs){
    return *this = *this - rhs;
}

//�������� ���������� �������� ������
IntHuge& IntHuge::operator +=(const IntHuge& rhs){
    return *this = *this + rhs;
}


//�������� ���������
IntHuge& IntHuge::operator *=(const IntHuge& rhs){
    return *this = *this * rhs;
}

IntHuge IntHuge::mul(unsigned int digit) const{
  IntHuge result;
  result.digits.clear();
  result.sign = true;
  unsigned int carry = 0;
  for(int i = digits.size()-1; i>=0; i--){ //������������ ����� ������� �����, ������� � ������� ��������
    unsigned int digitres = digits[i] * digit + carry; //���������� �� ������ �����
    if(digitres > 9){ //���������� ���������
      carry = digitres / 10;
      digitres %= 10;
    }
    else
      carry = 0;
    result.digits.push_back(digitres);
  }
  if(carry != 0)
    result.digits.push_back(carry);

  std::reverse(result.digits.begin(), result.digits.end());
  return result;
}

const IntHuge IntHuge::operator*(const IntHuge& rhs) const{
  IntHuge product;
  IntHuge psum;
  unsigned int zeros_to_insert = 0;
  for(int i = rhs.digits.size() - 1; i>=0; i--){
    unsigned int digit = rhs.digits[i];
    product = this->mul(digit);
    product.digits.insert(product.digits.end(), zeros_to_insert++, 0);
    psum = psum + product;
  }
  if(sign != rhs.sign)
    psum.sign = false;
  return psum;
}
