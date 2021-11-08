#include <iostream>
#include "IntHuge.h"
#include <fstream>

using namespace std;

int main()
{
  ifstream ifst("input.txt");
  ofstream ofst("output.txt");

  IntHuge a, b;

  ifst >> a >> b;
  ofst <<"Input values: "<<"a= "<< a<<" b="<<b<<endl;
  ofst <<"Results"<<endl;
  ofst <<"Operator == a==b: "<< (a==b)<<endl;
  ofst <<"Operator != a!=b: "<< (a!=b)<<endl;
  ofst <<"Operator >  a>b:  "<< (a>b)<<endl;
  ofst <<"Operator <  a<b:  "<< (a<b)<<endl;
  ofst <<"Operator >= a>=b: "<< (a>=b)<<endl;
  ofst <<"Operator <= a<=b: "<< (a<=b)<<endl;
  ofst <<"Operator +  a+b:  "<< (a+b).to_string()<<endl;
  ofst <<"Operator -  a-b:  "<< (a-b).to_string()<<endl;
  ofst <<"Operator *= a*=b: "<< (a*b).to_string()<<endl;
  ofst <<"Operator *  a*b:  "<< (a*b).to_string()<<endl;
  ofst <<"Operator -= a-=b: "<< (a-=b).to_string()<<endl;
  ofst <<"Operator += a+=b: "<< (a+=b).to_string()<<endl;
  ofst <<"Operator =  a=b:  "<<"a="<< (a=b)<<endl;

  return 0;
}
