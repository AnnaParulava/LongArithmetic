#include "IntHuge.h"


//Конструктор по умолчанию
IntHuge::IntHuge(){
  digits.push_back(0); //инициализировать массив цифр нулем
  sign = true; //установаить положительный знак
}


//Конструктор по строке
IntHuge::IntHuge(std::string number){
if (number[0] == '-') //анализируем первый символ на предмет знака
 this->sign = false;
else
 this->sign = true;

 int pos = isdigit(number[0]) ? 0 : 1;
 for(unsigned int i = pos; i < number.length(); i++){//остальные цифры помещаем в массив
    digits.push_back(number[i] - '0');    //при этом приобразуем символ в число
  }

  removeLeadingZeros(); //удалить ведущие нули
}

//Конструктор по длинному целому
IntHuge::IntHuge(long long number)
  : IntHuge(std::to_string(number)) { //преобразовать аргумент к типу string и передать управление соответствующему конструктору
}

//Конструктор копирования
IntHuge::IntHuge(const IntHuge& rhs){
  sign = rhs.sign;
  digits = rhs.digits;
}

//Приведение к строковому типу
std::string IntHuge::to_string() const{
  std::string str;
  if(!sign)
    str+="-";
  for(unsigned int i = 0; i < digits.size(); i++)
    str += std::to_string(digits.at(i));
  return str;
}

//Удаление ведущих нулей
void IntHuge::removeLeadingZeros(){
  while(digits.size() > 1 && digits.at(0) == 0)
    digits.erase(digits.begin(), digits.begin() + 1);
}

//Ввод
std::istream& operator>>(std::istream& ist, IntHuge& intHuge){
  std::string number;
  ist >> number;
  intHuge = IntHuge(number);
  return ist;
}

//Вывод
std::ostream& operator<<(std::ostream& ost, IntHuge& intHuge){
  ost << intHuge.to_string();
  return ost;
}

//Оператор присваивания
IntHuge& IntHuge::operator=(const IntHuge& rhs){
  if(this == &rhs) //проверка на самоприсваивание
    return *this;
  sign = rhs.sign;
  digits = rhs.digits;
  return *this;
}

//Оператор сравнения >
bool IntHuge::operator>(const IntHuge& rhs) const{

  //проверка знака
  if(sign && !rhs.sign) return true;
  if(!sign && rhs.sign) return false;

  //проверка количества чисел в числе
  if(digits.size() > rhs.digits.size())
    return sign;
  if(digits.size() < rhs.digits.size())
    return !sign;

  //сравнение разрядов, начиная со старших
  for(size_t i = 0; i < digits.size(); i++) {
    if(digits[i] > rhs.digits[i]) //Сравнение идет до первого различающегося символа
      return sign;
    if(digits[i] < rhs.digits[i])
      return !sign;
  }

  return false;
}

//Оператор сравнения <
bool IntHuge::operator<(const IntHuge& rhs) const{
  return !(*this == rhs) && !(*this > rhs);
}

//Оператор равенства ==
bool IntHuge::operator==(const IntHuge& rhs) const{
  return (sign == rhs.sign && digits == rhs.digits);
}

//Оператор равенства !=
bool IntHuge::operator!=(const IntHuge& rhs) const{
  return !(*this == rhs);
}

//Оператор сравнения <=
bool IntHuge::operator<=(const IntHuge& rhs) const{
  return (*this == rhs) || !(*this > rhs);
}

//Оператор сравнения >=
bool IntHuge::operator>=(const IntHuge& rhs) const{
  return (*this == rhs) || (*this > rhs);
}


//Получение модуля числа
IntHuge IntHuge::abs() const{
  IntHuge a(*this); //создать копию аргумента
  a.sign = true; //изменить у него флаг знака
  return a;
}

//Возвращает i-тый разряд числа или ноль если индекс отрицательный
int IntHuge::digit(int index) const {
  return index >= 0 ? digits[index] : 0;
}

//универсальный оператор сложения (в столбик)
const IntHuge IntHuge::operator+(const IntHuge& rhs) const{
  IntHuge sum;
  if(sign == rhs.sign){ //проверка одинаковый ли знак
    sum.digits.clear();
    sum.sign = sign;
    unsigned int carry = 0; //флаг переноса из предыдущего разряда
    int index1 = digits.size() - 1;
    int index2 = rhs.digits.size() - 1;
    while(index1 >=0 || index2 >= 0){ //складываются разряды чисел справа налево
      auto digitsum = this->digit(index1) + rhs.digit(index2) + carry;

      carry = digitsum / 10;
      digitsum %= 10;

      sum.digits.push_back(digitsum); //цифры к результату добавляются в конец
      index1--;
      index2--;
    }
    if(carry != 0)
      sum.digits.push_back(carry);
    std::reverse(sum.digits.begin(), sum.digits.end()); //перевернуть результат
  } else{ //вычитаем из большего по модулю
    if(this->abs() > rhs.abs()){
      sum = this->abs() - rhs.abs();
      sum.sign = sign;
    } else{
      sum = rhs.abs() - this->abs();
      sum.sign = rhs.sign; //знак результата совпадает с большим по модулю
    }
  }
  return sum;
}

//универсальный оператор разности
const IntHuge IntHuge::operator-(const IntHuge& rhs) const{
  IntHuge difference;
  if(sign == rhs.sign) { //проверка на одинаковые знаки
    if(this->abs() > rhs.abs() || this->abs() == rhs.abs()){ //вычитаем из большего меньшее по модулю
      difference.digits.clear();
      int index1 = digits.size() - 1;
      int index2 = rhs.digits.size() - 1;
      int borrow = 0;
      difference.sign = sign;
      while(index1 >= 0 || index2 >= 0){
        auto digitdiff = this->digit(index1) - rhs.digit(index2) - borrow;

        if(digitdiff < 0){//если разряд результата отрицательный - нужно "занять" 10
            borrow = 1;
            digitdiff += 10;
        } else borrow = 0;

        difference.digits.push_back(digitdiff);
        index1--;
        index2--;
      }
      std::reverse(difference.digits.begin(), difference.digits.end());
      difference.removeLeadingZeros();
    } else { //меняем знаки
      difference = (rhs - (*this));
      difference.sign = !difference.sign;
    }
  } else{ //знаки разнные, выполныется сложение
    difference = this->abs() + rhs.abs();
    difference.sign = sign;
  }
  return difference;
}

//оператор вычитания длинного целого
IntHuge& IntHuge::operator -=(const IntHuge& rhs){
    return *this = *this - rhs;
}

//оператор добавления длинного целого
IntHuge& IntHuge::operator +=(const IntHuge& rhs){
    return *this = *this + rhs;
}


//оператор умножения
IntHuge& IntHuge::operator *=(const IntHuge& rhs){
    return *this = *this * rhs;
}

IntHuge IntHuge::mul(unsigned int digit) const{
  IntHuge result;
  result.digits.clear();
  result.sign = true;
  unsigned int carry = 0;
  for(int i = digits.size()-1; i>=0; i--){ //перебираются цифры второго числа, начиная с младших разрядов
    unsigned int digitres = digits[i] * digit + carry; //умножаются на первое число
    if(digitres > 9){ //складываем результат
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
